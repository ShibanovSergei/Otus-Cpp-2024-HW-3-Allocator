#include <map>
#include "main.h"

using namespace std;

int main()
{
	cout << "HW 03 Allocator." << endl;

    const elemsNumType N = 10;

    int factorials[N] = { 1, 1 };

    for (elemsNumType i = 2; i < N; i++)
    {
        factorials[i] = i * factorials[i - 1];
        // cout << "key: " << i << "   fact: " << factorials[i] << endl;
    }

    // -----------------------------------------------------
    std::map<int, int> stdmap;
    for (short i = 0; i < N; i++)
    {
        stdmap.insert(std::make_pair(i, factorials[i]));
    }

    // -----------------------------------------------------
    // Instantiate std::map<int, int> with a my custom allocator with 10 elements maximum.
    // Fill with 10 elements, where key is a number from 0 to 9 and value is the factorial of the key.
    // Show all values ​​(key and value separated by a space) stored in the container.
    std::cout << "\n---- std::map with custom allocator" << endl;

    std::map<int, int, std::less<int>, hw03_allocator<std::pair<const int, int>, N>> stdmap_myalloc;

    for (int i = 0; i < N; i++)
    {
        stdmap_myalloc.insert(std::make_pair(i, factorials[i]));
    }
    for (const auto& p : stdmap_myalloc)
    {
        std::cout << p.first << " " << p.second << "\n";
    }

    // ----------------------------------------------------------------
    // Create an instance of container hw03_vector to store int values.
    std::cout << "\n--- custom vector with standart allocator" << endl;

    hw03_vector<int> cust_vect;
    for (elemsNumType i = 0; i < N; i++)
    {
        cust_vect.push_back(i);
    }

    for (elemsNumType i = 0; i < N; i++)
    {        
        cout << "custom vector " << i << ": " << cust_vect[i] << endl;
    }

    // -------------------------------------------------------------
    // Instantiate your own container to store int values ​​with a new allocator limited to 10 elements
    std::cout << "\n--- custom vector with custom allocator" << endl;

    hw03_vector<int, hw03_allocator<int, 10>> cust_vect_and_alloc;
    for (elemsNumType i = 0; i < N; i++)
    {
        cust_vect_and_alloc.push_back(i);
    }

    for (auto it = cust_vect_and_alloc.begin(); it != cust_vect_and_alloc.end(); ++it)
    {
        std::cout << *it << "\n";
    }

	return 0;
}
