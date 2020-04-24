#include <fstream>
#include <iostream>
#include <string>
struct Product
{
    std::string Name;
    double Price = 0.00;
    std::string Desc;
    Product* Next = NULL;
};

struct ProductList
{
    Product* First = NULL;
    int Size = 0;
};

double GetProductPrice(Product* product)
{
    double x = 0.00;
    std::cout << "Enter a price for " << product->Name << ": ";
    while (!(std::cin >> x))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\n[ERROR] - Invalid entry! Please enter a number for " << product->Name << ": ";
    }
    return x;
}

ProductList* initProductList()
{
    ProductList* inventory = new ProductList;
    inventory->First = new Product;
    //inventory->First->Next = NULL;
    inventory->Size = 0;
    return inventory;
}

Product* ReturnNewProductPointer(Product* previous, ProductList* inventory)
{
    Product* product = new Product;
    previous->Next = product;
    inventory->Size++;
    //product->Next = NULL;
    return product;
}

ProductList* ReadProductsFromFile(std::string filename)
{
    std::ifstream fin;
    std::string numberLine;
    ProductList* inventory = initProductList();
    Product* currentProduct = inventory->First;
    if (fin.eof())
    {
        std::cout << "[ERROR] - FILE IS EMPTY OR DOESN'T EXIST" << std::endl;
        inventory->First = NULL;
    }
    else
    {
        do
        {
            inventory->Size++;
            getline(fin, currentProduct->Name);
            fin >> currentProduct->Price;
            getline(fin, numberLine);
            getline(fin, currentProduct->Desc);
            currentProduct = ReturnNewProductPointer(currentProduct, inventory);
        } while (!fin.eof());
    }
    fin.close();
    return inventory;
}

void WriteNewProductsToFile(std::string filename, Product* product)
{
    std::ofstream fout;
    fout.open(filename, std::ios::app);
    std::cout << "Enter a Product Name: ";
    getline(std::cin, product->Name);
    product->Price = GetProductPrice(product);
    std::cout << "Describe " << product->Name << ": ";
    getline(std::cin, product->Desc);
    fout << product->Name << std::endl << product->Price << std::endl << product->Desc << std::endl;
    fout.close();
}

int main()
{
    std::string filename = "Inventory.txt";
    ProductList* inventory = ReadProductsFromFile(filename);

    delete inventory;
    std::cin.get();
    return 0;
}
