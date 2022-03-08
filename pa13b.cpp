/// @file pa13b.cpp
/// @author MILKIAS GHILOM
/// @date 03/06/2022
/// @brief This program unit test that test the Container.cpp that
/// makes sure the program is working properly. it took me 3 hours
/// to write and debug

#define CATCH_CONFIG_MAIN
#if defined __linux__
    #include <catch.hpp>
#elif defined __MACH__
    #include </opt/local/include/catch2/catch.hpp>
#else
    #include "catch.hpp"
#endif

#include <string>
#include <initializer_list>
#include <iomanip>
#include <algorithm>
#include <sstream>

#include "Container.hpp"

TEMPLATE_TEST_CASE("Container(size_type)","",char,int ,double) {
    Container<TestType> container;

    // Checking the size
    CHECK(container.size() == 0);
    CHECK(container.empty() == true);

    Container<TestType> container2(31);

    CHECK(container.size() == 0);
}

TEMPLATE_TEST_CASE("Container(const Container& other)", "", char, int, double) {
    Container<TestType> container {70, 71, 72};

    Container<TestType> container2(container);

    //checking all contaner coped to container2
    CHECK(container2.size() == 3);
    CHECK(std::equal(container.begin(), container.end(),
                     container2.begin(), container2.end()) == true);
}

TEMPLATE_TEST_CASE("Container(const std::initializer_list<value_type>& init",
                    "", char, int, double){
     Container<TestType> container { 68, 69, 64, 65 };

    // checking the size == 4
    CHECK(container.size() == 4);
    CHECK(container.empty() == 0);

    // checking the boundaries
    CHECK(container.find(68) == container.begin());
    CHECK(container.find(65) == (container.end() - 1));
}

TEST_CASE("~Container()") {}

TEMPLATE_TEST_CASE("empty()", "", char, int , double) {
    Container<TestType> container;

    CHECK(container.empty() == true);

    // checking after inserting
    container.push_back(66);
    CHECK(container.size() == 1);

    // removing all items in the Container and checks if the Container is empty
    container.clear();
    CHECK(container.empty() == true);
}

TEMPLATE_TEST_CASE("size()", "", char, int ,double) {
   Container<TestType> container;

    // checking if the Container size is zero before adding.
    CHECK(container.size() == 0);

    container.push_back(69);
    container.push_back(67);
    container.push_back(62);
    container.push_back(67);
    container.push_back(62);
    container.push_back(64);
    container.push_back(67);

    // testing if the Container have 7 items
    CHECK(container.size() == 7);

    // Checking size after two items has added and new memory is allocated.
    container.push_back(8);
    container.push_back(5);
    CHECK(container.size() == 9);
}

TEST_CASE("begin()") {}
TEST_CASE("begin() const") {}
TEST_CASE("end()") {}
TEST_CASE("end() const") {}

TEMPLATE_TEST_CASE("push_back()","", char, int, double ) {
    Container<TestType> container;

    container.push_back(69);
    container.push_back(67);
    container.push_back(62);

    container.push_back(67);
    container.push_back(62);
    container.push_back(64);
    container.push_back(67);

    container.push_back(62);
    container.push_back(63);
    container.push_back(66);

     typename Container<TestType>::const_pointer iter = container.begin();

    // Checks the inserted item is in the right postion of the
    // container before new memory allocation.
    CHECK(container.size() == 10);

    // Checks the boundary of the container
    CHECK(*(iter + 9) == 66);
}

TEMPLATE_TEST_CASE("erase()","", char, int, double) {
    Container<TestType> container { 69, 67, 62, 67, 62, 64, 61 };

     // checking on erasing duplicated number.
    container.erase(container.begin() + 1);
    CHECK(*(container.begin() + 1) == 62);

     // checking non duplicated number
    container.erase(container.begin() + 4);
    CHECK(*(container.begin() + 4) == 61);


    // deleting the front member
    container.erase(container.begin());
    CHECK(*(container.begin())== 62);

    // checking the size
    CHECK(container.size() == 4);
}

TEMPLATE_TEST_CASE("clear()", "", char, int, double) {
    Container<TestType> container { 68, 68, 70, 71 };
    container.clear();

    // checking  if it is empty
    CHECK(container.empty() == true);
}

TEMPLATE_TEST_CASE("swap(Container&)", "", char, int, double) {
    Container<TestType> container1{ 70, 71, 72, 73 , 74};
    Container<TestType> container2;

    container1.swap(container2);

    // checking if they swapped correctly
    CHECK(container2.size() == 5);
    CHECK(container1.empty() == true);
}

TEMPLATE_TEST_CASE("find()","", char, int, double) {
    Container<TestType> container { 70, 71, 72, 73 , 74 };

    // checking in middle and boundries
    CHECK(container.find(TestType{74}) == container.end() - 1);
    CHECK(container.find(TestType{75}) == container.end());
    CHECK(container.find(TestType{70}) == container.begin());
}

TEST_CASE("equal(const Container&, const Container&)") {
    Container<int> container1 { 70, 71, 72, 73, 74 };
    Container<int> container2 { 70, 71, 72, 73, 74 };
    Container<int> container3 { 70, 71, 72, 73, 75 };

    // Checking the equality
    CHECK(equal(container1, container2) == true);
    CHECK(equal(container1, container3) == false);
}

TEST_CASE("write(std::ostream&, const Container&)") {
    std::ostringstream output;

    Container<int> container;

    // testing with empty Container format.
    write(output, container);
    CHECK(output.str() == "{}");

    output.str("");

    // tests the format when items are in the Container.
    container.push_back(7);
    container.push_back(3);
    container.push_back(5);

    write(output, container);

    CHECK(output.str() == "{7,3,5}");
}

TEMPLATE_TEST_CASE("operator=()", "", char, int, double) {
    Container<TestType> container_1 {1, 2, 3, 4, 5, 6};
    Container<TestType> container_2;
    container_2 = container_1;

    CHECK(container_2.size() == 6);

    //CHECK(container_1.begin() == container_2.begin();
    CHECK(std::equal(container_1.begin(), container_1.end(),
                     container_2.begin(), container_2.end()) == true);
}

TEMPLATE_TEST_CASE("operator+=()", "", char, int, double) {
    Container<TestType> container_1{61, 62, 63, 64, 65, 66};
    Container<TestType> container_2{67, 68, 69, 70};
    Container<TestType> container_3;

    container_1 += container_2;

    // Check with exsting members
    CHECK(container_1.size() == 10);
    CHECK(container_2.size() == 4);
    CHECK(container_1.find(TestType{67}) == container_1.begin() + 6);
    CHECK(container_1.find(TestType{70}) == container_1.end() - 1);

    container_3 += container_2;

    // Check with empty Container
    CHECK(container_3.size() == 4);
}

TEMPLATE_TEST_CASE("bool operator==()", "", char, int, double) {
    Container<TestType> container_1{61, 62, 63, 64, 65, 66};
    Container<TestType> container_2{67, 68, 69, 70};
    Container<TestType> container_3{61, 62, 63, 64, 65, 66};

    // checking if the two Containers are equal
    CHECK(container_1 == container_3);
    CHECK((container_1 == container_2) == 0);
}

TEMPLATE_TEST_CASE("bool operator!=()", "", char, int, double) {
    Container<TestType> container_1{61, 62, 63, 64, 65, 66};
    Container<TestType> container_2{67, 68, 69, 70};
    Container<TestType> container_3{61, 62, 63, 64, 65, 66};

    // checking the equality
    CHECK(container_1 != container_2);
    CHECK((container_1 != container_3) == 0);

}
TEMPLATE_TEST_CASE("Container operator+()",
                    "", char, int, double) {
    Container<TestType> container_1{61, 62, 63, 64, 65, 66};
    Container<TestType> container_2{67, 68, 69, 70};
    Container<TestType> container_3;

    container_3 = container_1 + container_2;

    // adding the Container into the third Container
    CHECK(container_3.size() == 10);
    CHECK(*(container_3.begin()) == 61);
    CHECK(*(container_3.end() - 1) == 70);
}

TEST_CASE("std::ostream& operator<<(std::ostream& ,const Container<int>&)") {
    std::ostringstream output;
    Container<int> container_1{1, 2, 3, 4, 5, 6};
    Container<int> container_2;
    output << container_2;
    CHECK(output.str() == "{}");

    output.str("");
    output << container_1;

    // comparing the output
    CHECK(output.str() == "{1,2,3,4,5,6}");
}

TEST_CASE("operator<<(std::ostream&,const Container<std::string>&)") {
    const Container<std::string> REF {
        "Monday", "Tuesday", "Wednesday", "Thursday","Friday"
    };
    std::ostringstream output;
    Container<std::string> container_1{ REF };
    Container<std::string> container_2;
    output << container_2;
    CHECK(output.str() == "{}");

    output.str("");
    output << container_1;

    // comparing the output
    CHECK(output.str() == "{Monday,Tuesday,Wednesday,Thursday,Friday}");
}

/* EOF */
