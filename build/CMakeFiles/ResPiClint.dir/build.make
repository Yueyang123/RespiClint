# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pi/Desktop/WorkSpace/ResPiClint

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/Desktop/WorkSpace/ResPiClint/build

# Include any dependencies generated for this target.
include CMakeFiles/ResPiClint.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ResPiClint.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ResPiClint.dir/flags.make

CMakeFiles/ResPiClint.dir/src/gpio.cpp.o: CMakeFiles/ResPiClint.dir/flags.make
CMakeFiles/ResPiClint.dir/src/gpio.cpp.o: ../src/gpio.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/WorkSpace/ResPiClint/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ResPiClint.dir/src/gpio.cpp.o"
	/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ResPiClint.dir/src/gpio.cpp.o -c /home/pi/Desktop/WorkSpace/ResPiClint/src/gpio.cpp

CMakeFiles/ResPiClint.dir/src/gpio.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ResPiClint.dir/src/gpio.cpp.i"
	/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Desktop/WorkSpace/ResPiClint/src/gpio.cpp > CMakeFiles/ResPiClint.dir/src/gpio.cpp.i

CMakeFiles/ResPiClint.dir/src/gpio.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ResPiClint.dir/src/gpio.cpp.s"
	/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Desktop/WorkSpace/ResPiClint/src/gpio.cpp -o CMakeFiles/ResPiClint.dir/src/gpio.cpp.s

CMakeFiles/ResPiClint.dir/src/main.cpp.o: CMakeFiles/ResPiClint.dir/flags.make
CMakeFiles/ResPiClint.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/WorkSpace/ResPiClint/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ResPiClint.dir/src/main.cpp.o"
	/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ResPiClint.dir/src/main.cpp.o -c /home/pi/Desktop/WorkSpace/ResPiClint/src/main.cpp

CMakeFiles/ResPiClint.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ResPiClint.dir/src/main.cpp.i"
	/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Desktop/WorkSpace/ResPiClint/src/main.cpp > CMakeFiles/ResPiClint.dir/src/main.cpp.i

CMakeFiles/ResPiClint.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ResPiClint.dir/src/main.cpp.s"
	/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Desktop/WorkSpace/ResPiClint/src/main.cpp -o CMakeFiles/ResPiClint.dir/src/main.cpp.s

CMakeFiles/ResPiClint.dir/src/tcp_camera.cpp.o: CMakeFiles/ResPiClint.dir/flags.make
CMakeFiles/ResPiClint.dir/src/tcp_camera.cpp.o: ../src/tcp_camera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/WorkSpace/ResPiClint/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ResPiClint.dir/src/tcp_camera.cpp.o"
	/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ResPiClint.dir/src/tcp_camera.cpp.o -c /home/pi/Desktop/WorkSpace/ResPiClint/src/tcp_camera.cpp

CMakeFiles/ResPiClint.dir/src/tcp_camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ResPiClint.dir/src/tcp_camera.cpp.i"
	/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Desktop/WorkSpace/ResPiClint/src/tcp_camera.cpp > CMakeFiles/ResPiClint.dir/src/tcp_camera.cpp.i

CMakeFiles/ResPiClint.dir/src/tcp_camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ResPiClint.dir/src/tcp_camera.cpp.s"
	/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Desktop/WorkSpace/ResPiClint/src/tcp_camera.cpp -o CMakeFiles/ResPiClint.dir/src/tcp_camera.cpp.s

CMakeFiles/ResPiClint.dir/src/tcp_net_socket.cpp.o: CMakeFiles/ResPiClint.dir/flags.make
CMakeFiles/ResPiClint.dir/src/tcp_net_socket.cpp.o: ../src/tcp_net_socket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/WorkSpace/ResPiClint/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/ResPiClint.dir/src/tcp_net_socket.cpp.o"
	/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ResPiClint.dir/src/tcp_net_socket.cpp.o -c /home/pi/Desktop/WorkSpace/ResPiClint/src/tcp_net_socket.cpp

CMakeFiles/ResPiClint.dir/src/tcp_net_socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ResPiClint.dir/src/tcp_net_socket.cpp.i"
	/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Desktop/WorkSpace/ResPiClint/src/tcp_net_socket.cpp > CMakeFiles/ResPiClint.dir/src/tcp_net_socket.cpp.i

CMakeFiles/ResPiClint.dir/src/tcp_net_socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ResPiClint.dir/src/tcp_net_socket.cpp.s"
	/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Desktop/WorkSpace/ResPiClint/src/tcp_net_socket.cpp -o CMakeFiles/ResPiClint.dir/src/tcp_net_socket.cpp.s

# Object files for target ResPiClint
ResPiClint_OBJECTS = \
"CMakeFiles/ResPiClint.dir/src/gpio.cpp.o" \
"CMakeFiles/ResPiClint.dir/src/main.cpp.o" \
"CMakeFiles/ResPiClint.dir/src/tcp_camera.cpp.o" \
"CMakeFiles/ResPiClint.dir/src/tcp_net_socket.cpp.o"

# External object files for target ResPiClint
ResPiClint_EXTERNAL_OBJECTS =

ResPiClint: CMakeFiles/ResPiClint.dir/src/gpio.cpp.o
ResPiClint: CMakeFiles/ResPiClint.dir/src/main.cpp.o
ResPiClint: CMakeFiles/ResPiClint.dir/src/tcp_camera.cpp.o
ResPiClint: CMakeFiles/ResPiClint.dir/src/tcp_net_socket.cpp.o
ResPiClint: CMakeFiles/ResPiClint.dir/build.make
ResPiClint: /usr/local/lib/libopencv_stitching.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_superres.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_videostab.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_aruco.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_bgsegm.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_bioinspired.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_ccalib.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_dpm.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_face.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_freetype.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_fuzzy.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_img_hash.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_line_descriptor.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_optflow.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_reg.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_rgbd.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_saliency.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_stereo.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_structured_light.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_surface_matching.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_tracking.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_xfeatures2d.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_ximgproc.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_xobjdetect.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_xphoto.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_shape.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_photo.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_datasets.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_plot.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_text.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_dnn.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_ml.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_video.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_calib3d.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_features2d.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_highgui.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_videoio.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_phase_unwrapping.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_flann.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_imgcodecs.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_objdetect.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_imgproc.so.3.4.0
ResPiClint: /usr/local/lib/libopencv_core.so.3.4.0
ResPiClint: CMakeFiles/ResPiClint.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/Desktop/WorkSpace/ResPiClint/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable ResPiClint"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ResPiClint.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ResPiClint.dir/build: ResPiClint

.PHONY : CMakeFiles/ResPiClint.dir/build

CMakeFiles/ResPiClint.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ResPiClint.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ResPiClint.dir/clean

CMakeFiles/ResPiClint.dir/depend:
	cd /home/pi/Desktop/WorkSpace/ResPiClint/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Desktop/WorkSpace/ResPiClint /home/pi/Desktop/WorkSpace/ResPiClint /home/pi/Desktop/WorkSpace/ResPiClint/build /home/pi/Desktop/WorkSpace/ResPiClint/build /home/pi/Desktop/WorkSpace/ResPiClint/build/CMakeFiles/ResPiClint.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ResPiClint.dir/depend

