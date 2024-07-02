cmake_minimum_required(VERSION 3.4)
project(Library)
include(FetchContent)

FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
        GIT_TAG v3.10.3)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

set(SOURCE_FILES
        src/model/Address.cpp include/model/Address.h
        src/model/Client.cpp include/model/Client.h
        src/model/Parcel.cpp include/model/Parcel.h
        src/model/Order.cpp include/model/Order.h
        src/model/Standard.cpp include/model/Standard.h
        src/model/Carefull.cpp include/model/Carefull.h
        src/repositories/ClientRepository.cpp include/repositories/ClientRepository.h
        src/repositories/ParcelRepository.cpp include/repositories/ParcelRepository.h
        src/repositories/OrderRepository.cpp include/repositories/OrderRepository.h
        src/managers/ClientManager.cpp include/managers/ClientManager.h
        src/managers/OrderManager.cpp include/managers/OrderManager.h
        src/managers/ParcelManager.cpp include/managers/ParcelManager.h
        include/typedefs.h
        src/exceptions/ClientException.cpp include/exceptions/ClientException.h
        src/exceptions/OrderException.cpp include/exceptions/OrderException.h
        src/exceptions/ParcelException.cpp include/exceptions/ParcelException.h src/repositories/StorageContainer.cpp include/repositories/StorageContainer.h include/repositories/Repository.h include/SavingState.h)

#Utwórz bibliotekę typu STATIC, SHARED albo MODULE ze wskazanych źródeł
add_library(Library ${SOURCE_FILES})

target_include_directories(Library PUBLIC include)
target_link_libraries(Library nlohmann_json::nlohmann_json)

# dodane do testow
enable_testing()
find_package (Boost 1.60.0 COMPONENTS "unit_test_framework" REQUIRED)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)

set(SOURCE_TEST_FILES
        test/master.cpp
        test/OrderTest.cpp test/RepositoriesTest.cpp test/ManagersTest.cpp
        test/ClientTest.cpp test/ParcelTest.cpp test/AddressTest.cpp)
add_executable (Test ${SOURCE_TEST_FILES})

#dołącz bibliotekę z testowanymi klasami oraz bibliotekę boost.test do programu testów
target_link_libraries (Test
        Library
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        )

#dodaj test TestBiblioteki1. Instrukcji cmake add_test może być wiele.
#Dodatkowe parametry wpływają na szczegółowość generowanego raportu. Standardowo znajduje się on w Testing/Temporary.
add_test(LibraryTest Test
        --report_level=detailed
        --log_level=all
        --color_output=yes
        )
add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
        ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --verbose
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})