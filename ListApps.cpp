// ListApps.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include "ArrayList.h"
#include "SimpleList.h"
using namespace std;


string testValues[]     = { "a", "b", "c", "d", "e" };
int testValuesLength = sizeof(testValues) / sizeof(testValues[0]);
string advancedValues[] = { "a", "b", "a", "d", "b" };
int advancedValuesLength = sizeof(advancedValues) / sizeof(advancedValues[0]);

void testEmpty(SimpleList &list)
{
    try
    {
        int size = list.size();
        printf("Empty Test - size() %s\n", size == 0 ? "passed" : "failed- expected 0 got " + size);
    } catch (const exception& e)
    {
        printf("Empty Test - size() failed- expected 0 got Exception\n");
    }

    try
    {
        printf("Empty Test - isEmpty() %s\n", list.isEmpty() ? "passed" : "failed- expected true got false");
    }
    catch (const exception& e)
    {
        printf("Empty Test - isEmpty() failed- expected true got Exception\n");
    }

    try
    {
        string result = list.remove(1);
        printf("Empty Test - remove(1) %s\n", (result.length() == 0 ? "passed" : "failed- expected NULL got " + result).c_str());
    }
    catch (const exception& e)
    {
        printf("Empty Test - remove(1) failed- expected NULL got Exception\n");
    }

    try
    {
        string result = list.get(1);
        printf("Empty Test - get(1) %s\n", (result.length() == 0 ? "passed" : "failed- expected NULL got " + result).c_str());
    }
    catch (const exception& e)
    {
        printf("Empty Test - get(1) failed- expected NULL got Exception\n");
    }

    try
    {
        string result = list.get(1);
        printf("Empty Test - set(1) %s\n", (result.length() == 0 ? "passed" : "failed- expected NULL got " + result).c_str());
    }
    catch (const exception& e)
    {
        printf("Empty Test - set(1) failed- expected NULL got Exception\n");
    }
}

/**
 * Fills the provided list with the test values.
 * Should be classed after the Happy Path test of add is confirmed
 * @param list the list to fill
 */
void fillList(SimpleList &list, string with[], int n)
{
    for (int i = 0; i < n; i++)
    {
        list.add(with[i]);
    }
}

void testHappyPaths(SimpleList &list)
{
    // ..........Test adds
    try
    {
        bool passed = true;
        int count = 0;
        for (string value : testValues)
        {
            bool result = list.add(value);
            count = count + 1;
            if (!result)
            {
                passed = false;
                printf("Happy Path Test - add(%s) returned false when expected true\n", value.c_str());
            }
            int size = list.size();
            if (size != count)
            {
                passed = false;
                printf("Happy Path Test - size() returned %d when expected %d\n", count, size);
            }
        }
        printf("Happy Path Test - add() and size() %s\n", passed ? "passed" : "failed");
    }
    catch (const exception& e)
    {
        printf("Happy Path Test - add(1) failed- expected NULL got Exception\n");
    }

    // ..........Test get
    try
    {
        bool passed = true;
        for (int i = 0; i < testValuesLength; i++)
        {
            string value = list.get(i);
            if (! (testValues[i] == value))
            {
                passed = false;
                printf("Happy Path Test - get() failed- got %s, expected %s\n", value.c_str(), testValues[i].c_str());
            }
        }
        printf("Happy Path Test - get() %s\n", passed ? "passed" : "failed");
    }
    catch (const exception& e)
    {
        printf("Happy Path Test - get() failed- got Exception\n");
    }

    //........Test Set
    try
    {
        bool passed = true;
        for (int i = 0; i < testValuesLength; i++)
        {
            int reverseValue = testValuesLength - 1 - i;
            string value = list.set(i, testValues[reverseValue]);
            if (value != testValues[i])
            {
                passed = false;
                string expected = testValues[i];
                printf("Happy Path Test - set() failed- got %s, expected %s\n", value.c_str(), expected.c_str());
            }

            value = list.get(i);
            if (! (testValues[reverseValue] == value))
            {
                passed = false;
                printf("Happy Path Test - get() after set() failed- got %s, expected %s\n", value.c_str(), testValues[reverseValue].c_str());
            }
        }
        printf("Happy Path Test - set() %s\n", passed ? "passed" : "failed");
    }
    catch (const exception& e)
    {
        printf("Happy Path Test - set() failed- got Exception\n");
    }

    // .............. Test clear()
    try
    {
        list.clear();
        int size = list.size();
        if (size == 0 && list.isEmpty())
        {
            printf("Happy Path Test - clear() passed\n");
        }
        else
        {
            printf("Happy Path Test - clear() failed- got: %d or isEmpty()= %s\n", size, (list.isEmpty() ? "true" : "false"));
        }
    }
    catch (const exception& e)
    {
        printf("Happy Path Test - clear() failed- got Exception\n");
    }


    //........Test Remove
    try
    {
        bool passed = true;
        fillList(list, testValues, testValuesLength);
        for (int i = 0; i < testValuesLength; i++)
        {
            string value = list.remove(0);
            if (value != testValues[i])
            {
                passed = false;
                printf("Happy Path Test - remove(forward) failed- got %s, expected %s\n", value.c_str(), testValues[i].c_str());
            }
        }

        fillList(list, testValues, testValuesLength);
        for (int i = testValuesLength - 1; i >= 0; i--)
        {
            string value = list.remove(i);
            if (value != testValues[i])
            {
                passed = false;
                printf("Happy Path Test - remove(backward) failed- got %s, expected %s\n", value.c_str(), testValues[i].c_str());
            }
        }

        fillList(list, testValues, testValuesLength);
        std::list<string> exemplar;
        for (int i = 0; i < testValuesLength; i++)
        {
            exemplar.push_back(testValues[i]);
        }
        while (! list.isEmpty())
        {
            int index = list.size() / 2;
            string value = list.remove(index);
            string expected;
            { // This goes to get and then remove the next item on the exemplar C++ list
                std::list<string>::iterator i = exemplar.begin();
                advance(i, index);
                expected = *i;
                exemplar.remove(expected);
            }
            if (value != expected)
            {
                passed = false;
                printf("Happy Path Test - remove(middle) failed- got %s, expected %s\n", value.c_str(), expected.c_str());
            }
        }

        printf("Happy Path Test - remove() %s\n", passed ? "passed" : "failed");
    }
    catch (const exception& e)
    {
        printf("Happy Path Test - remove() failed- got Exception\n");
    }
}

void edgeCases(SimpleList &list)
{
    list.clear();
    fillList(list, testValues, testValuesLength);

    //........Test Outside Bounds
    try
    {
        bool passed = true;
        string value;
        value = list.get(-1);
        if (value.length() > 0 || list.size() != testValuesLength)
        {
            passed = false;
            printf("Edge Cases Test - get(-1) failed- got %s, expected NULL\n", value.c_str());
        }
        value = list.set(-1, "!");
        if (value.length() > 0 || list.size() != testValuesLength)
        {
            passed = false;
            printf("Edge Cases Test - set(-1) failed- got %s, expected NULL\n", value.c_str());
        }
        value = list.remove(-1);
        if (value.length() > 0 || list.size() != testValuesLength)
        {
            passed = false;
            printf("Edge Cases Test - remove(-1) failed- got %s, expected NULL\n", value.c_str());
        }
        printf("Edge Cases Test - negative indicies %s\n", passed ? "passed" : "failed");
    }
    catch (const exception& e)
    {
        printf("Edge Cases Test - negative indicies failed- got Exception\n");
    }

    try
    {
        bool passed = true;
        string value;
        value = list.get(6);
        if (value.length() > 0 || list.size() != testValuesLength)
        {
            passed = false;
            printf("Edge Cases Test - get(6) failed- got %s, expected NULL\n", value.c_str());
        }
        value = list.set(6, "!");
        if (value.length() > 0 || list.size() != testValuesLength)
        {
            passed = false;
            printf("Edge Cases Test - set(6) failed- got %s, expected NULL\n", value.c_str());
        }
        value = list.remove(6);
        if (value.length() > 0 || list.size() != testValuesLength)
        {
            passed = false;
            printf("Edge Cases Test - remove(6) failed- got %s, expected NULL\n", value.c_str());
        }
        printf("Edge Cases Test - too large indicies %s\n", passed ? "passed" : "failed");
    }
    catch (const exception& e)
    {
        printf("Edge Cases Test - too large indicies failed- got Exception\n");
    }
}

void testAdvanced(AdvancedList &list)
{
    list.clear();
    fillList(list, advancedValues, advancedValuesLength);
    try
    {
        bool passed = true;
        if (!(list.contains("a") && list.contains("b")))
        {
            passed = false;
            printf("Advanced Happy Path Test - contains() failed, did not contain expected values\n");
        }

        if (list.contains("c"))
        {
            passed = false;
            printf("Advanced Happy Path Test - contains() failed, should not contain value \"c\"\n");
        }
        printf("Advanced Happy Path Test - contains() %s\n", passed ? "passed" : "failed");
    }
    catch (const exception& e)
    {
        printf("Advanced Happy Path Test - contains() failed- got Exception\n");
    }

    std::list<string> exemplar;
    for (int i = 0; i < advancedValuesLength; i++)
    {
        exemplar.push_back(advancedValues[i]);
    }

    try
    {
        bool passed = true;
        int value = list.indexOf("a");
        int expected = 0;
        { // Go find the first example in a C++ list
            for (std::list<string>::iterator i = exemplar.begin(); i != exemplar.end(); i++)
            {
                if (*i == "a")
                {
                    break;
                }
                expected = expected + 1;
            }
            if (expected == exemplar.size())
            {
                expected = -1;
            }
        }
        if (value != expected)
        {
            passed = false;
            printf("Advanced Happy Path Test - indexOf(\"a\") failed, got %d, expected %d\n", value, expected);
        }
        value = list.indexOf("c");
        if (value != -1)
        {
            passed = false;
            printf("Advanced Happy Path Test - indexOf(\"c\") failed, got %d, expected -1\n", value);
        }

        printf("Advanced Happy Path Test - indexOf() %s\n", passed ? "passed" : "failed");
    }
    catch (const exception& e)
    {
        printf("Advanced Happy Path Test - indexOf() failed- got Exception\n");
    }
    
    try
    {
        bool passed = true;
        int value = list.lastIndexOf("a");
        int expected = exemplar.size() - 1;
        { // Go find the last example in a C++ list
            for (std::list<string>::iterator i = exemplar.end(); i != exemplar.begin();)
            {
                i--; // must do this first on this one
                if (*i == "a")
                {
                    break;
                }
                expected = expected - 1;
            }
        }
        if (value != expected)
        {
            passed = false;
            printf("Advanced Happy Path Test - lastIndexOf(\"a\") failed, got %d, expected %d\n", value, expected);
        }
        value = list.lastIndexOf("c");
        if (value != -1)
        {
            passed = false;
            printf("Advanced Happy Path Test - lastIndexOf(\"c\") failed, got %d, expected -1\n", value);
        }
        printf("Advanced Happy Path Test - lastIndexOf() %s\n", passed ? "passed" : "failed");
    }
    catch (const exception& e)
    {
        printf("Advanced Happy Path Test - lastIndexOf() failed- got Exception\n");
    }

    //........Test Remove
    try
    {
        bool passed = true;
        for (int i = 0; i < advancedValuesLength; i++)
        {
            if (! list.remove(advancedValues[i]))
            {
                passed = false;
                printf("Advanced Happy Path Test - remove(by string forward) failed- returned false\n");
            }
        }

        fillList(list, advancedValues, advancedValuesLength);
        for (int i = advancedValuesLength - 1; i >= 0; i--)
        {
            if (!list.remove(advancedValues[i]))
            {
                passed = false;
                printf("Advanced Happy Path Test - remove(by string backward) failed- returned false on %s at %d\n", advancedValues[i].c_str(), i);
            }
        }

        printf("Advanced Happy Path Test - remove(by string) %s\n", passed ? "passed" : "failed");
    }
    catch (const exception& e)
    {
        printf("Advanced Happy Path Test - remove(by string) failed- got Exception\n");
    }
}

void advancedEdgeCases(AdvancedList &list)
{
    list.clear();
    fillList(list, advancedValues, advancedValuesLength);

    //........Test Outside Bounds
    try
    {
        bool passed = true;
        int value;
        value = list.indexOf("c");
        if (value != -1)
        {
            passed = false;
            printf("Advanced Edge Cases Test - indexOf(\"c\") failed- got %c, expected -1\n", value);
        }
        value = list.lastIndexOf("c");
        if (value != -1)
        {
            passed = false;
            printf("Advanced Edge Cases Test - indexOf(\"c\") failed- got %c, expected -1\n", value);
        }
        if (list.remove("c"))
        {
            passed = false;
            printf("Advanced Edge Cases Test - remove(\"c\") failed- reported true\n");
        }
        printf("Advanced Edge Cases Test - not present %s\n", passed ? "passed" : "failed");
    }
    catch (const exception& e)
    {
        printf("Advanced Edge Cases Test - negative indicies failed- got Exception\n");
    }
}


template<typename Base, typename T>
inline bool instanceof(const T*)
{
    return is_base_of<Base, T>::value;
}




int main()
{
    ArrayList listUnderTest;

    testHappyPaths(listUnderTest);
    testEmpty(listUnderTest);
    edgeCases(listUnderTest);
    
    AdvancedList* advancedListUnderTest = dynamic_cast<AdvancedList*>(&listUnderTest);
    if (advancedListUnderTest != nullptr)
    {
        testAdvanced(*advancedListUnderTest);
        advancedEdgeCases(*advancedListUnderTest);
    }
}