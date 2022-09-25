#include <cmath>                                                      // abs(), pow()
#include <iomanip>                                                    // quoted()
#include <iostream>
#include <string>
#include <type_traits>                                                // is_floating_point_v, common_type_t
#include <utility>                                                    // move()

#include "book.hpp"

/*******************************************************************************
**  Constructors, assignments, and destructor
*******************************************************************************/

// Default and Conversion Constructor
Book::Book(const std::string& title,
           const std::string& author,
           const std::string& isbn,
           double price)
{
  //Book book(title, author, isbn, 4);
  title_ = std::move(title);
  author_ = std::move(author);
  isbn_ = std::move(isbn);
  price_ = price;
}


// Copy constructor
Book::Book( Book const & other )
{
  //Book b2(b1);
  title_ = other.title_;
  author_ = other.author_;
  isbn_ = other.isbn_;
  price_ = other.price_;
}




// Copy Assignment Operator
Book & Book::operator=( const Book& rhs )
{
  //.....Book b2;
  //b2 = b1;
  if(this == &rhs)
  {
    return *this;
  }
  else
  {
    title_ = rhs.title();
    author_ = rhs.author();
    isbn_ = rhs.isbn();
    price_ = rhs.price();

    return *this;
  }
}



// Destructor
Book::~Book() noexcept
{
  //no need to use key word delete because there are no pointers
}








/*******************************************************************************
**  Accessors
*******************************************************************************/
//1 & returns a l-value (a variable that contains memory)
// isbn() const
std::string const & Book::isbn() const
{
  return isbn_;
}




// title() const
std::string const & Book::title() const
{
  return title_;
}




// author() const
std::string const & Book::author() const
{
  return author_;
}



// price() const
double Book::price() const
{
  return price_;
}



//2 & returns a r-value (std::move() makes the l-value into an temporary value)
// isbn()
std::string Book::isbn()
{
  return std::move(isbn_);
}




// title()
std::string Book::title()
{
  return std::move(title_);
}




// author()
std::string Book::author()
{
  return std::move(author_);
}








/*******************************************************************************
**  Modifiers
*******************************************************************************/

// isbn()
Book & Book::isbn(const std::string& new_isbn )
{
  isbn_ = new_isbn;
  return *this;
}




// title()
Book & Book::title(const std::string& new_title)
{
  title_ = new_title;
  return *this;
}




// author()
Book & Book::author(const std::string& new_author )
{
  author_ = new_author;
  return *this;
}




// price()
Book & Book::price( double new_price )
{
  price_ = new_price;
  return *this;
}



/*******************************************************************************
**  Relational Operators
*******************************************************************************/


// operator==
bool Book::operator==( const Book & rhs ) const noexcept
{
  // All attributes must be equal for the two books to be equal to the other.  This can be done in any order, so put the quickest
  // and then the most likely to be different first.
  if(price_ == rhs.price() && author_ == rhs.author() &&
    title_ == rhs.title() && isbn_ == rhs.isbn())
  {
    return true;
  }
  return false;
}

// operator!=
bool Book::operator!=( const Book & rhs ) const noexcept
{
  // Two books are unequal if any of their attributes are unequal.
  return(!(*this == rhs));
}

// operator<
bool Book::operator<( const Book & rhs ) const noexcept
{
  // Books are ordered (sorted) by ISBN, author, title, then price.
  // return std::tie(isbn_, author_, title_, price_)
  //      < std::tie(rhs.isbn_, rhs.author_, rhs.title_, rhs.price_);
  if(isbn_ < rhs.isbn())
  {
    return true;
  }
  else if (isbn_ == rhs.isbn())
  {
    if(author_ < rhs.author())
    {
      return true;
    }
    else if(author_ == rhs.author())
    {
      if(title_ < rhs.title())
      {
        return true;
      }
      else if(title_ == rhs.title())
      {
        if(price_ < rhs.price())
        {
          return true;
        }
        else if(price_ == rhs.price())
        {
          return false;
        }
        else
          return false;
      }
      else
        return false;
    }
    else
      return false;
  }
  else
    return false;
}

// operator<=
bool Book::operator<=( const Book & rhs ) const noexcept
{
  // Books are ordered (sorted) by ISBN, author, title, then price.
  return !(*this > rhs);
}

// operator>
bool Book::operator>( const Book & rhs ) const noexcept
{
  // Books are ordered (sorted) by ISBN, author, title, then price.
  return rhs < *this;
}

// operator>=
bool Book::operator>=( const Book & rhs ) const noexcept
{
  // Books are ordered (sorted) by ISBN, author, title, then price.
  return !(*this < rhs);
}







/*******************************************************************************
**  Insertion and Extraction Operators
*******************************************************************************/

// operator>>
std::istream & operator>>( std::istream & stream, Book & book )
{
    /// A lot can go wrong when reading from streams - no permission, wrong types, end of file, etc. Minimal exception guarantee says
    /// there should be no side affects if an error or exception occurs, so let's do our work in a local object and move it into place
    /// at the end if all goes well.
    ///
    /// This function should be symmetrical with operator<< below.  Read what your write, and write what you read
    ///
    ///
    /// Assume fields are separated by commas and string attributes are enclosed with double quotes.  For example:
    ///    ISBN             | Title                 | Author             | Price
    ///    -----------------+-----------------------+--------------------+-----
    ///    "9789998287532",   "Over in the Meadow",   "Ezra Jack Keats",   91.11
    ///
    ///
    /// Hint:  Use std::quoted to read and write quoted strings.  See
    ///        1) https://en.cppreference.com/w/cpp/io/manip/quoted
    ///        2) https://www.youtube.com/watch?v=Mu-GUZuU31A
    char comma;
    stream >> std::quoted(book.isbn_) >> comma >> std::quoted(book.title_) >> comma
      >> std::quoted(book.author_) >> comma >> book.price_;
    return stream;
}




// operator<<
std::ostream & operator<<( std::ostream & stream, const Book & book )
{//fixed output,
  stream << std::quoted(book.isbn_) << ", " << std::quoted(book.title_) << ", "
    << std::quoted(book.author_) << ", " << book.price_ << '\n';
  return stream;
}
