#include <uxr/client/transport.h>

#include <microros_transports.h>
#include <version.h>

#if ZEPHYR_VERSION_CODE >= ZEPHYR_VERSION(3,1,0)
    #include <zephyr/kernel.h>
    #include <zephyr/device.h>
    #include <zephyr/sys/printk.h>
    #include <zephyr/drivers/can.h>
    #include <zephyr/posix/unistd.h>
#else
    #include <zephyr.h>
    #include <device.h>
    #include <sys/printk.h>
    #include <drivers/can.h>
    #include <posix/unistd.h>
#endif

#include <stdio.h>
#include <string.h>
#include <stdbool.h>



// --- micro-ROS CAN Transport for Zephyr ---


CAN_MSGQ_DEFINE(can_rx_msgq, 64);
int filter_id;






bool zephyr_transport_open(struct uxrCustomTransport * transport)
{
    zephyr_transport_params_t * params = (zephyr_transport_params_t*) transport->args;
    const struct device * can_dev = (const struct device *) params->can_dev;
    if (!device_is_ready(can_dev)) {
		printf("CAN: Device %s not ready.\n", can_dev->name);
		return false;
	}
   
    const struct can_filter can_rx_filter = {
        //Support for Zephyr 3.5.0 (already End of Life) , and Zephyr 3.6.0, and 3.7.0
        #if ZEPHYR_VERSION_CODE == ZEPHYR_VERSION(3,5,0)
        .flags =  CAN_FILTER_DATA | CAN_FILTER_FDF | CAN_FILTER_IDE ,
        #elif (ZEPHYR_VERSION_CODE >= ZEPHYR_VERSION(3,6,0)) && ZEPHYR_VERSION_CODE <= ZEPHYR_VERSION(3,7,0)
            .flags = CAN_FILTER_DATA | CAN_FILTER_IDE,
        #endif
        .id = (uint32_t) params->can_id,

        /*Have to look more into what range of CAN IDs to filter for micro-ROS messages. 
        For now we will assume that the whole bus will be used exlusively for micro-ROS */
        .mask =  0x1FFFF000U
    };
    
   
    int ret = can_set_mode(can_dev,  CAN_MODE_FD  );
    ret = can_start(can_dev);

    int filter_id;
    filter_id = can_add_rx_filter_msgq(can_dev, &can_rx_msgq, &can_rx_filter);
   
    if (filter_id < 0) 
    {
     printf("Unable to add rx filter [%d]\n", filter_id);
    }
    else
    {
        printf("Filter id: %d\n", filter_id);
    }

    return true;
}

bool zephyr_transport_close(struct uxrCustomTransport * transport)
{
    zephyr_transport_params_t * params = (zephyr_transport_params_t*) transport->args;
    const struct device * can_dev = (const struct device *) params->can_dev;
    return can_stop(can_dev);
    
}

void tx_irq_callback(const struct device *dev, int error, void *user_data)
{
        char *sender = (char *)user_data;

        if (error != 0) {
                printf("Sending failed [%d]\nSender: %s\n", error, sender);
        }
}


size_t zephyr_transport_write(struct uxrCustomTransport* transport, const uint8_t * buf, size_t len, uint8_t * err){
    zephyr_transport_params_t * params = (zephyr_transport_params_t*) transport->args;
    const struct device * can_dev = (const struct device *) params->can_dev;
    struct can_frame frame = {
        .flags = CAN_FRAME_FDF | CAN_FRAME_IDE ,
        .id = (uint32_t) params->can_id, 
        .dlc = can_bytes_to_dlc(len+1),
    };
    

    memcpy(&(frame.data[1]),buf,len);
    frame.data[0]= (uint8_t) len;
    can_send(can_dev, &frame,  K_FOREVER, tx_irq_callback, "Sender 1");
   
    return len;
}

size_t zephyr_transport_read(struct uxrCustomTransport* transport, uint8_t* buf, size_t len, int timeout, uint8_t* err){
    struct can_frame rx_frame;
    rx_frame.data[0] = 0;
    
    uint32_t queue_count =  k_msgq_num_used_get(&can_rx_msgq);

    k_msgq_get(&can_rx_msgq, &rx_frame, K_MSEC(timeout));
    queue_count =  k_msgq_num_used_get(&can_rx_msgq);
   
    uint8_t received_bytes = rx_frame.data_32[0];
   
    if(received_bytes > len)
    {
        printf("Error Received bytes > len \n");
        *err=1;
        return 0;
    }
    
    memcpy(buf,&(rx_frame.data[1]),received_bytes);
    
    
    return received_bytes;
    
}