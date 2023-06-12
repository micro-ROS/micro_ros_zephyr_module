^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for package micro_ros_zephyr
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Forthcoming
-----------
* Update repos to iron (`#122 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/122>`_)
* Update rolling sources (`#120 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/120>`_)
* Fix Zephyr headers for UDP transport (`#108 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/108>`_) (`#114 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/114>`_)
* Adjust default_params initialization for cpp compatibility (`#107 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/107>`_) (`#111 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/111>`_)
* Ignore test_msgs (`#99 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/99>`_) (`#102 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/102>`_)
* Fix headers and timer (`#94 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/94>`_) (`#97 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/97>`_)
* transports: add mising version.h to serial-usb transport header (`#90 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/90>`_) (`#91 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/91>`_)
* Use ZEPHYR_VERSION_CODE instead of KERNEL_VERSION_MAJOR (`#86 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/86>`_)
* Fix/zephyr includes (`#82 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/82>`_) (`#85 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/85>`_)
* Add rosidl_core (`#75 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/75>`_)
* Fix nightly (`#69 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/69>`_) (`#71 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/71>`_)
* Move support to v2.7.x and v3.1.0 (`#64 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/64>`_)

4.0.0 (2022-05-25)
------------------
* Update banner (`#56 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/56>`_)
* Merge pull request `#54 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/54>`_ from micro-ROS/mergify/bp/main/pr-53
* [FIX] pass zephyr MTU config to UClient
* Add logos (`#50 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/50>`_)
* Fix Rolling includes (`#49 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/49>`_)
* Fix CI (`#46 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/46>`_)
* Fix include paths
* Fix include paths (`#45 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/45>`_)
* Fix example and serial transports (`#36 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/36>`_) (`#39 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/39>`_)
* Add typesupport introspection (backport `#37 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/37>`_) (`#38 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/38>`_)
* multichange tool (`#31 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/31>`_) (`#33 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/33>`_)
* Hotfix: Zephyr gcc typesupport error (`#27 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/27>`_)
* Update from 2.6.0rc1 to 2.6.0 (`#30 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/30>`_)
* Add micro_ros_utilities repo (`#23 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/23>`_)
* Enable introspection (`#21 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/21>`_)
* Initial changes for Rolling release
* Fix CI (`#25 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/25>`_)
* Add v2.5/v2.6 (`#24 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/24>`_)
* Simplify Colcon installation (`#19 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/19>`_)
* Modify RMW API include (`#16 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/16>`_)
* Fix RCLC Foxy (`#17 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/17>`_)
* Update RCLC repo (`#15 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/15>`_)
* Refactor external transports (`#14 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/14>`_)
* Add issue template
* Add nightly CI
* Update ci.yml
* Add new micro_ros_msgs repo (`#13 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/13>`_)
* rclc_executor_set_timeout (`#12 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/12>`_)
* rework demos (`#11 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/11>`_)
* Update main.c (`#10 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/10>`_)
* Remove explicit C++ support (fixes `#4 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/4>`_) (`#9 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/9>`_)
* README: Fix docker command for the serial micro-ROS agent (`#8 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/8>`_)
* Update README.md
* Update README.md
* update ranlib (`#3 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/3>`_)
* Update README.md
* Update CI (`#5 <https://github.com/micro-ROS/micro_ros_zephyr_module/issues/5>`_)
* Add preliminary CI
* Fix copyright
* Remove sample.yml
* Added license and README
* Updated Kconfig uros params
* Initial
* Initial commit
