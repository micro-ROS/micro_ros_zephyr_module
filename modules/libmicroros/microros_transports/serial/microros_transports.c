#include <uxr/client/transport.h>

#include <zephyr.h>

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include <microros_transports.h>

#include <device.h>
#include <sys/printk.h>
#include <drivers/uart.h>
#include <sys/ring_buffer.h>

#define RING_BUF_SIZE 2048

char uart_in_buffer[RING_BUF_SIZE];
char uart_out_buffer[RING_BUF_SIZE];

struct ring_buf out_ringbuf, in_ringbuf;

// --- micro-ROS Serial Transport for Zephyr ---

static void uart_fifo_callback(const struct device * dev, void * args){
    while (uart_irq_update(dev) && uart_irq_is_pending(dev)) {
        if (uart_irq_rx_ready(dev)) {
            int recv_len;
            char buffer[64];
            size_t len = MIN(ring_buf_space_get(&in_ringbuf), sizeof(buffer));

            if (len > 0){
                recv_len = uart_fifo_read(dev, buffer, len);
                ring_buf_put(&in_ringbuf, buffer, recv_len);
            }

        }
    }
}


bool zephyr_transport_open(struct uxrCustomTransport * transport){
    zephyr_transport_params_t * params = (zephyr_transport_params_t*) transport->args;

    char uart_descriptor[8];
    sprintf(uart_descriptor,"UART_%d", params->fd);
    params->uart_dev = device_get_binding(uart_descriptor);
    if (!params->uart_dev) {
        printk("Serial device not found\n");
        return false;
    }

    ring_buf_init(&in_ringbuf, sizeof(uart_in_buffer), uart_out_buffer);

    uart_irq_callback_set(params->uart_dev, uart_fifo_callback);

    /* Enable rx interrupts */
    uart_irq_rx_enable(params->uart_dev);

    return true;
}

bool zephyr_transport_close(struct uxrCustomTransport * transport){
    (void) transport;
    // TODO: close serial transport here
    return true;
}

size_t zephyr_transport_write(struct uxrCustomTransport* transport, const uint8_t * buf, size_t len, uint8_t * err){
    zephyr_transport_params_t * params = (zephyr_transport_params_t*) transport->args;

    for (size_t i = 0; i < len; i++)
    {
        uart_poll_out(params->uart_dev, buf[i]);
    }

    return len;
}

size_t zephyr_transport_read(struct uxrCustomTransport* transport, uint8_t* buf, size_t len, int timeout, uint8_t* err){
    zephyr_transport_params_t * params = (zephyr_transport_params_t*) transport->args;

    size_t read = 0;
    int spent_time = 0;

    while(ring_buf_is_empty(&in_ringbuf) && spent_time < timeout){
        usleep(1000);
        spent_time++;
    }

    uart_irq_rx_disable(params->uart_dev);
    read = ring_buf_get(&in_ringbuf, buf, len);
    uart_irq_rx_enable(params->uart_dev);

    return read;
}