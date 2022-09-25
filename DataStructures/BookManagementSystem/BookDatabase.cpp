#include "BookDatabase.hpp"

  /// Include necessary header files.
  ///
  /// Do not put anything else in this section, i.e. comments, classes,
  /// functions, etc.  Only #include directives.
#include <vector>
#include <fstream>
#include <string>

const std::string kDatabaseFilename = "database.txt";

// Return a reference to the one and only instance of the database
BookDatabase & BookDatabase::instance() {
  static BookDatabase theInstance( kDatabaseFilename );
  return theInstance;
}

BookDatabase::BookDatabase( const std::string & filename ) {
  std::ifstream fin( filename, std::ios::binary );

  // The file contains Books separated by whitespace. A Book has 4 pieces of
  // data delimited with a comma. This exactly matches the previous assignment
  // as to how Books are read.
  //
  //       Field            Type            Notes
  //  1.   Book's ISBN      String          Unique identifier (primary key), always enclosed in double quotes
  //  2.   Book's Title     String          May contain spaces, always enclosed in double quotes
  //  3.   Book's Author    String          May contain spaces, always enclosed in double quotes
  //  4.   Book's Price     Floating Point  In dollars
  //
  //  Example:
  //    "0001062417",  "Early aircraft",                 "Maurice F. Allward", 65.65
  //    "0000255406",  "Shadow maker \"1st edition)\"",  "Rosemary Sullivan",   8.08
  //    "0000385264",  "Der Karawanenkardinal",          "Heinz Gstrein",      35.18
  //
  // NOTE: Double quotes within the string are escaped with the backslash
  // character.
  //

    /// HINT:  Use your Book's extraction operator to read Books, don't reinvent
    /// that here. Read books until end of file, pushing each book into the data
    /// store as they are read.
    std::string data;//place holder for getline()
    Book book;
  if(fin)
  {
    while(getline(fin, data))//while data is still being read
    {
      fin >> book;
      _book_database.push_back(book);
    }
  }

  // NOTE: The file is intentionally not explicitly closed. The file is closed
  // when fin goes out of scope - for whatever reason. More precisely, the
  // object `fin` is destroyed when it goes out of scope and the file is closed
  // in the destructor. See RAII.
}

  /// Implement the rest of the interface, including functions find
  /// (recursively) and size.
  ///
  /// Programming note:  An O(n) operation, like searching an unsorted vector,
  /// would not generally be implemented recursively. The depth of recursion
  /// may be greater than the program's function call stack size. But for this
  /// programming exercise, getting familiar with recursion is a goal.
Book * BookDatabase::find( const std::string & isbn )
{
  int check = find_rec(isbn, &(*_book_database.begin()), 0); // size_t
  if(check == -1) // nothing was found
  {
    return nullptr;
  }
  else
  {
    return &(_book_database[check]);
  }
}
std::size_t BookDatabase::find_rec( const std::string & isbn, Book * size, int count )
{
  if(count == _book_database.size())
  {
    return -1;//if at the end of datatbase
  }
  if(isbn == size->isbn())
  {
    return count;//if found at this location _book_database[count];
  }
  else
    return find_rec(isbn, ++size, ++count);//cycles through the database

}
std::size_t BookDatabase::size() const
{
  return _book_database.size();
}
