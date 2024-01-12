#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <set>

// define a set to store member ids
std::set<int> mySet;
//vectors to store book names and tokens from the csv file
std::vector<std::string> Bookname;
std::vector<std::string> tokens;
// variable to store the data of book issue
int dateOfIssue;
class Person;

class Book;
// Creating Date Class to represent date info
class Date
{
public:
    int day, month, year;
};
// Creating Person Class
class Person
{
private:
    std::string name;
    std::string address;
    std::string email;

public:
  //constructors and getter setters for name , address and email
    Person() : name(""), address(""), email("") {}

    Person(const std::string &name, const std::string &address, const std::string &email)
        : name(name), address(address), email(email) {}

    virtual ~Person() {}

    virtual void dummyFunction() {}

    std::string getName() const
    {
        return name;
    }

    void setName(const std::string &newName)
    {
        name = newName;
    }

    std::string getAddress() const
    {
        return address;
    }

    void setAddress(const std::string &newAddress)
    {
        address = newAddress;
    }

    std::string getEmail() const
    {
        return email;
    }

    void setEmail(const std::string &newEmail)
    {
        email = newEmail;
    }
};

// Creating Book class
class Book : public Person
{
private:
    int bookID;
    std::string bookName;
    std::string authorFirstName;
    std::string authorLastName;
    std::string bookType;
    Date dueDate;
    Person *borrower;

public:
    Book(int bookID, const std::string &bookName, const std::string &authorFirstName,
         const std::string &authorLastName)
        : bookID(bookID), bookName(bookName), authorFirstName(authorFirstName),
          authorLastName(authorLastName), borrower(nullptr) {}

    int getBookID() const
    {
        return bookID;
    }

    std::string getBookName() const
    {
        return bookName;
    }

    std::string getAuthorFirstName() const
    {
        return authorFirstName;
    }

    std::string getAuthorLastName() const
    {
        return authorLastName;
    }

    Date getDueDate() const
    {
        return dueDate;
    }

    void setDueDate(const Date &newDueDate)
    {
        dueDate = newDueDate;
    }

    void returnBook();

    void borrowBook(Person *borrower, const Date &dueDate);
};

// creating Member class
class Member : public Person
{
private:
  // member attributes
    int memberID;
    std::vector<Book *> booksLoaned;

public:
    Member(int memberID, const std::string &name, const std::string &address, const std::string &email)
        : Person(name, address, email), memberID(memberID) {}

    int getMemberID() const
    {
        return memberID;
    }

    const std::vector<Book *> &getBooksBorrowed() const
    {
        return booksLoaned;
    }
  // constructors and getter setters for member attributes
    void setBooksBorrowed(Book *book);
};
// creating librarian class
class Librarian : public Person
{
private:
  //librarian attributes
    int staffID;
    int salary;
    std::vector<Member *> members;

public:
    Librarian(int staffID, const std::string &name, const std::string &address, const std::string &email, int salary)
        : Person(name, address, email), staffID(staffID), salary(salary) {}

    int getStaffID() const
    {
        return staffID;
    }

    void setStaffID(int newStaffID)
    {
        staffID = newStaffID;
    }

    int getSalary() const
    {
        return salary;
    }

    void setSalary(int newSalary)
    {
        salary = newSalary;
    }

    void addMember(Member *member);

    void issueBook(int memberID, int bookID);

    void returnBook(int memberID, int bookID);

    void displayBorrowedBooks(int memberID);

    void calcFine(int memberID);
};
//methods for book class
void Book::returnBook()
{
    borrower = nullptr;
}
// Creating BorrowBook Class
void Book::borrowBook(Person *borrower, const Date &dueDate)
{
    if (this->borrower == nullptr)
    {
        this->borrower = borrower;
        this->dueDate = dueDate;
        if (dynamic_cast<Member *>(this->borrower) != nullptr)
        {
            dynamic_cast<Member *>(this->borrower)->setBooksBorrowed(this);
        }
    }
    else
    {
        std::cerr << "Error: Book already borrowed" << std::endl;
    }
}
// method for member class
void Member::setBooksBorrowed(Book *book)
{
    booksLoaned.push_back(book);
}
// methods for librarian class
void Librarian::addMember(Member *member)
{
    members.push_back(member);
}
// method to issue a book to a member
void Librarian::issueBook(int memberID, int bookID)
{
}
// method to return a book from a member
void Librarian::returnBook(int memberID, int bookID)
{
}
// method to display the books borrowed by a member
void Librarian::displayBorrowedBooks(int memberID)
{
}
// method to display the fine for the members
void Librarian::calcFine(int memberID)
{
}
// class to handle the user interface
class showInterface
{
public:
    // Creating Master Class to display the options for a librarian
    void master()
    {
        int i;
        std::cout << "\n\t***** WELCOME LIBRARIAN *****\n";
        std::cout << "\n\t\t>>Please Choose One Option:\n";
        std::cout << "\n\t\t1.Return Book\n\n\t\t2.Add Member\n\n\t\t3.Issue Book\n\n\t\t4.Close Application\n";
        std::cout << "\n\t\tEnter your choice : ";
        std::cin >> i;
        switch (i)
        {

        case 1:
            returnBook();
            break;
        case 2:
            addMember();
            break;
        case 3:
            issueBook();
            break;
        case 4:
            exit(0);
        default:
            std::cout << "\n\t\tPlease enter correct option :(";

            system("cls");
        }
    }
  // methods for librarian actions
    void issueBook()
    {
        std::string B_name;
        std::cout << "Enter Book Name" << std::endl;
        std::cin >> B_name;

        if (B_name == "Big" || B_name == "Nature")
        {

            std::cout << "\t\t Enter Today's Date \n\n";
            std::cin >> dateOfIssue;
            std::cout << "\t\t *******Book Issued*******\n\n";
            master();
        }
        else
        {
            std::cout << "\t\t Book Not Found" << std::endl;
            master();
        }
    }

    void fine()
    {
        int date;
        std::cout << "\t\t Enter Today's Date" << std::endl;
        std::cin >> date;
        if (date - dateOfIssue > 3)
        {
            std::cout << "\t\t Total Fine is :" << (date - dateOfIssue -3) << " Pounds" << std::endl;
            master();
        }
        else
            std::cout << "\t\tNo Fine \n\n"
                      << "\t\tBook Successful Returned \n\n"
                      << std::endl;
                      master();
    }
    void returnBook()
    {
        fine();
    }
  // methods for student access
    void stdId()
    {
        int myId;
        std::cout << "\t\tEnter ID" << std::endl;
        std::cin >> myId;
        auto pos = mySet.find(myId);
        if (pos != mySet.end())
        {
            std::cout << "\t\t *******Login Successful*******\n\n";
            disciple();
        }
        else
        {
            std::cout << "Not A Member" << std::endl;
            return;
        }
    }
    void addMember()
    {
        int myId;
        std::cout << "Enter ID" << std::endl;
        std::cin >> myId;
        mySet.insert(myId);
        std::cout << "\t\t Member Added" << std::endl;
        showing();
    }
    void disciple()
    {
        int i;
        std::cout << "\n\t***** WELCOME STUDENT *****\n";
        std::cout << "\n\t\t>>Please Choose One Option:\n";
        std::cout << "\n\t\t1.View BookList\n\n\t\t2.Search for a Book\n\n\t\t3.Go to main menu\n\n\t\t4.Close Application\n";
        std::cout << "\n\t\tEnter your choice : ";
        std::cin >> i;
        if (i == 1)
            std::cout << "BookList";
        else if (i == 2)
            std::cout << "Searching";
        else if (i == 3)
        {
            system("cls");
        }
        else
        {
            std::cout << "\n\t\tPlease enter correct option :(";
            system("cls");
        }
    }
  // method to enter a password for librarian access
    void key()
    {
        int i = 0;
        std::string ch, ch1 = "pass";
        std::cout << "\n\t\tEnter Password : ";
        while (1)
        {
            std::cin >> ch;
            if (ch == ch1)
            {
                std::cout << "\t\t****Login Successfull**" << std::endl;
                master();
            }
            else
            {
                std::cout << "\n\n\t\tWrong Password.\n\n\t\ttry again.....\n";
                system("cls");
                showing();
            }
        }
    }
  // main function to display the initial options for users
    void showing()
    {
        int i;
        std::cout << "\n\t***** LIBRARY MANAGEMENT SYSTEM *****\n"
                  << "\n\t\t\t    L M S C++\n";
        std::cout << "\n\t\t>>Please Choose Any Option To login \n";
        std::cout << "\n\t\t1.Student\n\n\t\t2.Librarian\n\n\t\t3.Close Application\n";
        std::cout << "\n\t\tEnter your choice : ";
        std::cin >> i;
        if (i == 1)
        {
            stdId();
            system("cls");
        }
        else if (i == 2)
        {
            key();
        }
        else
        {
            std::cout << "\n\t\tPlease enter correct option :(";
            system("CLS");
        }
    }
};
// main function starts here
int main()
{
  // opeining the csv file containing library data
    std::ifstream file;
    showInterface my;

    file.open("library_data.csv", std::ios::in);
    // checking if the file is opening successfully
    if (!file)
    {
        std::cerr << "Error: Unable to open file" << std::endl;
    }
    // reading data from the csv file
    std::string line;
    int num = 1;
    int num2 = 1;
    while (!file.eof())
    {
        std::getline(file, line);
        std::istringstream iss(line);

        while (std::getline(iss, line, ','))
        {
            num++;
            num2++;
            tokens.push_back(line);
            if (num == 3)
            {
                Bookname.push_back(line);
                num2 = 1;
            }
            if ((num2 % 6) + 1 == 2)
            {
                Bookname.push_back(line);
            }
        }
    }
    // closing the file
    file.close();
    // displaying the initial options for users
    my.showing();

    return 0;
}
