#include <iostream>
#include <string>
#include <regex>

std::string getFirstPartOfURL(const std::string &url)
{
    size_t secondSlashPos = url.find('/', 1);
    if (secondSlashPos != std::string::npos)
    {
        return url.substr(0, secondSlashPos);
    }
    return url;
}

int main()
{
    std::string url = "/dbmanager/a";

    std::string firstPart = getFirstPartOfURL(url);

    if (!firstPart.empty())
    {
        std::cout << "First part of the URL: " << firstPart << std::endl;
    }
    else
    {
        std::cout << "Failed to extract the first part of the URL." << std::endl;
    }

    return 0;
}
