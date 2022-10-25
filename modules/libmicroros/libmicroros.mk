UROS_DIR = $(COMPONENT_PATH)/micro_ros_src
DEBUG ?= 0

ifeq ($(DEBUG), 1)
	BUILD_TYPE = Debug
else
	BUILD_TYPE = Release
endif

CFLAGS_INTERNAL := $(CFLAGS)
CXXFLAGS_INTERNAL := $(CXXFLAGS)

CFLAGS_INTERNAL := -c -I$(ZEPHYR_BASE)/include/posix -I$(PROJECT_BINARY_DIR)/include/generated $(CFLAGS_INTERNAL)
CXXFLAGS_INTERNAL := -c -I$(ZEPHYR_BASE)/include/posix -I$(PROJECT_BINARY_DIR)/include/generated $(CXXFLAGS_INTERNAL)

all: $(COMPONENT_PATH)/libmicroros.a

clean:
	rm -rf $(COMPONENT_PATH)/libmicroros.a; \
	rm -rf $(COMPONENT_PATH)/include; \
	rm -rf $(COMPONENT_PATH)/zephyr_toolchain.cmake; \
	rm -rf $(COMPONENT_PATH)/micro_ros_dev; \
	rm -rf $(COMPONENT_PATH)/micro_ros_src;

ZEPHYR_CONF_FILE := $(PROJECT_BINARY_DIR)/.config

configure_colcon_meta: $(COMPONENT_PATH)/colcon.meta $(COMPONENT_PATH)/micro_ros_src/src
	. $(COMPONENT_PATH)/utils.sh; \
	cp $(COMPONENT_PATH)/colcon.meta $(COMPONENT_PATH)/configured_colcon.meta; \
	ZEPHYR_CONF_FILE=$(ZEPHYR_CONF_FILE); \
	update_meta_from_zephyr_config "CONFIG_MICROROS_NODES" "rmw_microxrcedds" "RMW_UXRCE_MAX_NODES"; \
	update_meta_from_zephyr_config "CONFIG_MICROROS_PUBLISHERS" "rmw_microxrcedds" "RMW_UXRCE_MAX_PUBLISHERS"; \
	update_meta_from_zephyr_config "CONFIG_MICROROS_SUBSCRIBERS" "rmw_microxrcedds" "RMW_UXRCE_MAX_SUBSCRIPTIONS"; \
	update_meta_from_zephyr_config "CONFIG_MICROROS_CLIENTS" "rmw_microxrcedds" "RMW_UXRCE_MAX_CLIENTS"; \
	update_meta_from_zephyr_config "CONFIG_MICROROS_SERVERS" "rmw_microxrcedds" "RMW_UXRCE_MAX_SERVICES"; \
	update_meta_from_zephyr_config "CONFIG_MICROROS_RMW_HISTORIC" "rmw_microxrcedds" "RMW_UXRCE_MAX_HISTORY"; \
	update_meta_from_zephyr_config "CONFIG_MICROROS_XRCE_DDS_HISTORIC" "rmw_microxrcedds" "RMW_UXRCE_STREAM_HISTORY"; \
	update_meta_from_zephyr_config "CONFIG_MICROROS_XRCE_DDS_MTU" "microxrcedds_client" "UCLIENT_CUSTOM_TRANSPORT_MTU"; \
	update_meta "microxrcedds_client" "UCLIENT_PROFILE_SERIAL=OFF"; \
	update_meta "microxrcedds_client" "UCLIENT_PROFILE_UDP=OFF"; \
	update_meta "microxrcedds_client" "UCLIENT_PROFILE_TCP=OFF"; \
	update_meta "microxrcedds_client" "UCLIENT_PROFILE_CUSTOM_TRANSPORT=ON"; \
	update_meta "microxrcedds_client" "UCLIENT_PROFILE_STREAM_FRAMING=ON"; \
	update_meta "rmw_microxrcedds" "RMW_UXRCE_TRANSPORT=custom";


configure_toolchain: $(COMPONENT_PATH)/zephyr_toolchain.cmake.in
	rm -f $(COMPONENT_PATH)/zephyr_toolchain.cmake; \
	cat $(COMPONENT_PATH)/zephyr_toolchain.cmake.in | \
		sed "s/@CMAKE_C_COMPILER@/$(subst /,\/,$(CC))/g" | \
		sed "s/@CMAKE_CXX_COMPILER@/$(subst /,\/,$(CXX))/g" | \
		sed "s/@CMAKE_SYSROOT@/$(subst /,\/,$(COMPONENT_PATH))/g" | \
		sed "s/@CFLAGS@/$(subst /,\/,$(CFLAGS_INTERNAL))/g" | \
		sed "s/@CXXFLAGS@/$(subst /,\/,$(CXXFLAGS_INTERNAL))/g" \
		> $(COMPONENT_PATH)/zephyr_toolchain.cmake

$(COMPONENT_PATH)/micro_ros_dev/install:
	rm -rf micro_ros_dev; \
	mkdir micro_ros_dev; cd micro_ros_dev; \
	git clone -b foxy https://github.com/ament/ament_cmake src/ament_cmake; \
	git clone -b foxy https://github.com/ament/ament_lint src/ament_lint; \
	git clone -b foxy https://github.com/ament/ament_package src/ament_package; \
	git clone -b foxy https://github.com/ament/googletest src/googletest; \
	git clone -b foxy https://github.com/ros2/ament_cmake_ros src/ament_cmake_ros; \
	colcon build; 

$(COMPONENT_PATH)/micro_ros_src/src:
	rm -rf micro_ros_src; \
	mkdir micro_ros_src; cd micro_ros_src; \
	git clone -b foxy https://github.com/eProsima/micro-CDR src/micro-CDR; \
	git clone -b foxy https://github.com/eProsima/Micro-XRCE-DDS-Client src/Micro-XRCE-DDS-Client; \
	git clone -b foxy https://github.com/micro-ROS/rcl src/rcl; \
	git clone -b foxy https://github.com/ros2/rclc src/rclc; \
	git clone -b foxy https://github.com/micro-ROS/rcutils src/rcutils; \
	git clone -b foxy https://github.com/micro-ROS/micro_ros_msgs src/micro_ros_msgs; \
	git clone -b foxy https://github.com/micro-ROS/rmw-microxrcedds src/rmw-microxrcedds; \
	git clone -b foxy https://github.com/micro-ROS/rosidl_typesupport src/rosidl_typesupport; \
	git clone -b foxy https://github.com/micro-ROS/rosidl_typesupport_microxrcedds src/rosidl_typesupport_microxrcedds; \
	git clone -b master https://github.com/ros2/tinydir_vendor src/tinydir_vendor; \
	git clone -b foxy https://github.com/ros2/rosidl src/rosidl; \
	git clone -b foxy https://github.com/ros2/rmw src/rmw; \
	git clone -b foxy https://github.com/ros2/rcl_interfaces src/rcl_interfaces; \
	git clone -b foxy https://github.com/ros2/rosidl_defaults src/rosidl_defaults; \
	git clone -b foxy https://github.com/ros2/unique_identifier_msgs src/unique_identifier_msgs; \
	git clone -b foxy https://github.com/ros2/common_interfaces src/common_interfaces; \
	git clone -b foxy https://github.com/ros2/test_interface_files src/test_interface_files; \
	git clone -b foxy https://github.com/ros2/rmw_implementation src/rmw_implementation; \
	git clone -b foxy_microros https://gitlab.com/micro-ROS/ros_tracing/ros2_tracing src/ros2_tracing; \
	touch src/rosidl/rosidl_typesupport_introspection_c/COLCON_IGNORE; \
    touch src/rosidl/rosidl_typesupport_introspection_cpp/COLCON_IGNORE; \
    touch src/rclc/rclc_examples/COLCON_IGNORE; \
	touch src/rcl/rcl_yaml_param_parser/COLCON_IGNORE; \
    touch src/rcl_interfaces/test_msgs/COLCON_IGNORE;

$(COMPONENT_PATH)/micro_ros_src/install: configure_colcon_meta configure_toolchain $(COMPONENT_PATH)/micro_ros_dev/install $(COMPONENT_PATH)/micro_ros_src/src
	cd $(UROS_DIR); \
	. ../micro_ros_dev/install/local_setup.sh; \
	colcon build \
		--merge-install \
		--packages-ignore-regex=.*_cpp \
		--metas $(COMPONENT_PATH)/configured_colcon.meta \
		--cmake-args \
		"--no-warn-unused-cli" \
		-DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=OFF \
		-DTHIRDPARTY=ON \
		-DBUILD_SHARED_LIBS=OFF \
		-DBUILD_TESTING=OFF \
		-DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
		-DCMAKE_TOOLCHAIN_FILE=$(COMPONENT_PATH)/zephyr_toolchain.cmake \
		-DCMAKE_VERBOSE_MAKEFILE=OFF; \

$(COMPONENT_PATH)/libmicroros.a: $(COMPONENT_PATH)/micro_ros_src/install
	mkdir -p $(UROS_DIR)/libmicroros; cd $(UROS_DIR)/libmicroros; \
	for file in $$(find $(UROS_DIR)/install/lib/ -name '*.a'); do \
		folder=$$(echo $$file | sed -E "s/(.+)\/(.+).a/\2/"); \
		mkdir -p $$folder; cd $$folder; $(AR) x $$file; \
		for f in *; do \
			mv $$f ../$$folder-$$f; \
		done; \
		cd ..; rm -rf $$folder; \
	done ; \
	$(AR) rc libmicroros.a *.obj; cp libmicroros.a $(COMPONENT_PATH); ${RANLIB} $(COMPONENT_PATH)/libmicroros.a; \
	cd ..; rm -rf libmicroros; \
	cp -R $(UROS_DIR)/install/include $(COMPONENT_PATH)/include;
