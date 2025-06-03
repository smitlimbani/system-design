cmake_minimum_required(VERSION 3.15)
project(system-design)

# Add subdirectories but don't build everything by default
# Only the selected project will be configured when chosen in VSCode

add_subdirectory(Demo EXCLUDE_FROM_ALL)
add_subdirectory(LRUCache EXCLUDE_FROM_ALL)
add_subdirectory(VendingMachine EXCLUDE_FROM_ALL)