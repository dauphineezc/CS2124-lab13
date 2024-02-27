// Zoe Dauphinee, recitation 13, STL 
// vectors and lists, half-open range, iterators, auto, generic algorithms, functors and lambdas, templated functions, maps and sets

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;


void print_list(const list<int>& lst);
void print_list_w_range(const list<int>& lst);
void print_alts_w_auto(const list<int>& lst);
list<int>::const_iterator find_list_item(const list<int>& lst, int target);
list<int>::const_iterator find_using_find(const list<int>& lst, int target);
bool check_if_even(int num);
list<int>::const_iterator find_if_even(const list<int>& lst);
int* find_using_find_array(int* array, int array_size, int target);
int* find_if_even_array(int* array, int array_size);
list<int>::const_iterator ourFind(list<int>::const_iterator start, list<int>::const_iterator end, int target);

// defined up here bc otherwise error:
// "error: function 'find_list_item_auto' with deduced return type cannot be used before it is defined"
auto find_list_item_auto(const list<int>& lst, int target) {
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        if (*it == target) {
            cout << *it;
            return it;
        }
    }
    cout << "that value does not exist in the list";
    return lst.end();
}

template<typename Iterator, typename Target>
Iterator ourFind (Iterator start, Iterator end, const Target& target) { 
    cout << "checking template ourFind...\n";
    for (Iterator it = start; it != end; ++it) {
        if (*it == target) {
            cout << *it;
            return it;
        }
    }
    cout << "that value does not exist";
    return end;
};

class EvenChecker {
    public:
        bool operator()(int num) const {
            return num % 2 == 0;
        }
};


int main() {

    //
    // Vector and List Basics
    //

    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";

    vector<int> vect {2, 8, 10, 6, 4, 12};
    for (size_t index = 0; index < vect.size(); ++index) {
        cout << vect[index] << " ";
    }

    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";

    list<int> lst(vect.begin(), vect.end());
    for (int num : lst) {
        cout << num << " ";
    }

    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";

    sort(vect.begin(), vect.end());

    for (size_t index = 0; index < vect.size(); ++index) {
        cout << vect[index] << " ";
    }
    cout << endl;
    for (int num : lst) {
        cout << num << " ";
    }

    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";

    for (size_t index = 0; index < vect.size(); index += 2) {
        cout << vect[index] << " ";
    }

    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";

    //for (size_t index = 0; index < lst.size(); index += 2) {
        //cout << lst[index] << " ";
    //}

    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";

    for (vector<int>::iterator it = vect.begin(); it != vect.end(); it += 2) {
        cout << *it << " ";
    }

    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";

    for (list<int>::iterator it = lst.begin(); it != lst.end();) {
        cout << *it << " ";

        if (++it != lst.end()) {
            ++it;
        }
    }

    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";

    lst.sort();
    for (int num : lst) {
        cout << num << " ";
    }

    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";

    print_list(lst);
    cout << endl;

    cout << "=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";

    print_list_w_range(lst);
    cout << endl;

    cout << "=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";

    print_alts_w_auto(lst);
    cout << endl;

    cout << "=======\n";

    
    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";

    find_list_item(lst, 8);
    cout << endl;
    find_list_item(lst, 45);
    cout << endl;

    cout << "=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";

    find_list_item_auto(lst, 8);
    cout << endl;
    find_list_item_auto(lst, 45);
    cout << endl;

    cout << "=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";

    find_using_find(lst, 8);
    cout << endl;

    cout << "=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";

    find_if_even(lst);
    cout << endl;

    cout << "=======\n";

    // 16. Functor
    cout << "Task 16:\n";

    find_if_even(lst);
    cout << endl;

    cout << "=======\n";
    
    // 17. Lambda
    cout << "Task 17:\n";

    [] { cout << "Hello Lambda!"; } ();
    cout << endl;

    [] (int a, int b) { cout << a + b << endl; } (4, 5);

    int result = [] (int a, int b) { return a + b; } (4, 5);
    cout << "the result is: " << result << endl;

    int result2 = [] (int a, int b) -> int { return a + b; } (4, 5);
    cout << "the result is: " << result2 << endl;

        // using a lambda expression to find first even number
    list<int>::iterator it = find_if(lst.begin(), lst.end(), [] (int i) { return i % 2 == 0; });
    if (it != lst.end()) {
        cout << *it;
    } 
    else {
        cout << "no even value exists in the list";
    }
    cout << endl;

    cout << "=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";

    int* array = new int[6];
    copy(lst.begin(), lst.end(), array);

    for (size_t index = 0; index < 6; index++) {
        cout << array[index] << " ";
    }
    cout << endl;

        // find certain element in the array
    find_using_find_array(array, 6, 8);
    cout << endl;
    find_using_find_array(array, 6, 45);
    cout << endl;

        // find first even element in the array
    find_if_even_array(array, 6);
    cout << endl;

    delete[] array;

    cout << "=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";

    ourFind(lst.begin(), lst.end(), 8);
    cout << endl;

    ourFind(lst.begin(), lst.end(), 45);
    cout << endl;

    cout << "=======\n";
    
    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    
        // vector (should use template)
    ourFind(vect.begin(), vect.end(), 8);
    cout << endl;
    ourFind(vect.begin(), vect.end(), 45);
    cout << endl;

        // list (should use function)
    ourFind(lst.begin(), lst.end(), 8);
    cout << endl;
    ourFind(lst.begin(), lst.end(), 45);
    cout << endl;

    cout << "=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";

        // open the file
    ifstream file;
    file.open("pooh-nopunc.txt");
    while (!file) {
        cerr << "failed to open file\n";
        exit(1);
    }

        // fill vector with unique tokens
    vector<string> tokens;
    string token;
    while (file >> token) {
        if (find(tokens.begin(), tokens.end(), token) == tokens.end()) {
            tokens.push_back(token);
        }
    }

    file.close();

        // print size and all tokens
    cout << "Number of unique tokens: " << tokens.size() << endl;
    for (size_t index = 0; index < tokens.size(); ++index) {
        cout << tokens[index] << " ";
    }
    cout << endl;

    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";

        // open the file
    file.open("pooh-nopunc.txt");
    while (!file) {
        cerr << "failed to open file\n";
        exit(1);
    }

        // fill set with unique tokens
    set<string> tokens_set;
    string token2;
    while (file >> token2) {
        tokens_set.insert(token2);
    }

    file.close();

        // print size and all tokens
    cout << "Number of unique tokens: " << tokens_set.size() << endl;
    for (const auto& word : tokens_set) {
        cout << word << " ";
    }
    cout << endl;

    cout << "=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";

        // open the file
    file.open("pooh-nopunc.txt");
    while (!file) {
        cerr << "failed to open file\n";
        exit(1);
    }

        // fill map with unique tokens
    map<string, vector<int>> wordMap;
    string token3;
    int position = 0;
    while (file >> token3) {
        wordMap[token3].push_back(position);
        position++;
    }

    file.close();

        // print each word with all positions on a line
    for (const auto& pair : wordMap) {
        cout << pair.first << ": ";
        for (int position : pair.second) {
            cout << position << " ";
        }
        cout << endl;
    }

    cout << "=======\n";
}

void print_list(const list<int>& lst) {
    for (list<int>::const_iterator it = lst.begin(); it != lst.end(); ++it) {
        cout << *it << " ";
    }
}

void print_list_w_range(const list<int>& lst) {
    for (int num : lst) {
        cout << num << " ";
    }
}

void print_alts_w_auto(const list<int>& lst) {
    for (auto it = lst.begin(); it != lst.end();) {
        cout << *it << " ";

        if (++it != lst.end()) {
            ++it;
        }
    }
}

list<int>::const_iterator find_list_item(const list<int>& lst, int target) {
    for (list<int>::const_iterator it = lst.begin(); it != lst.end(); ++it) {
        if (*it == target) {
            cout << *it;
            return it;
        }
    }
    cout << "that value does not exist in the list";
    return lst.end();
}

list<int>::const_iterator find_using_find(const list<int>& lst, int target) {
    list<int>::const_iterator it = find(lst.begin(), lst.end(), target);
    if (it != lst.end()) {
        cout << *it;
        return it;
    } 
    cout << "that value does not exist in the list";
    return lst.end();
}

bool check_if_even(int num) {
    return num % 2 == 0;
}

list<int>::const_iterator find_if_even(const list<int>& lst) {
    // list<int>::const_iterator it = find_if(lst.begin(), lst.end(), check_if_even);
    EvenChecker is_even;
    list<int>::const_iterator it = find_if(lst.begin(), lst.end(), is_even);
    if (it != lst.end()) {
        cout << *it;
        return it;
    } 
    else {
        cout << "no even value exists in the list";
        return lst.end();
    }
}

int* find_using_find_array(int* array, int array_size, int target) {
    int* it = find(array, array + array_size, target);
    if (it != array + array_size) {
        cout << *it;
        return it;
    }
    cout << "that value does not exist in the array";
    return array + array_size;
}

int* find_if_even_array(int* array, int array_size) {
    EvenChecker is_even;
    int* it = find_if(array, array + array_size, is_even);
    if (it != array + array_size) {
        cout << *it;
        return it;
    } 
    else {
        cout << "no even value exists in the array";
        return array + array_size;
    }
}

list<int>::const_iterator ourFind(list<int>::const_iterator start, list<int>::const_iterator end, int target) {
    cout << "checking ourFind...\n";
    for (list<int>::const_iterator it = start; it != end; ++it) {
        if (*it == target) {
            cout << *it;
            return it;
        }
    }
    cout << "that value does not exist in the list";
    return end;
}

template<typename Iterator, typename Target>
Iterator ourFind (Iterator start, Iterator end, int target) { 
    cout << "checking template ourFind...\n";
    for (Iterator it = start; it != end; ++it) {
        if (*it == target) {
            cout << *it;
            return it;
        }
    }
    cout << "that value does not exist";
    return end;
};