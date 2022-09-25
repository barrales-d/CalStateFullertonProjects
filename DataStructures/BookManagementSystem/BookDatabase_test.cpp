// Unit tests for the BookDatabase class.

#include "BookDatabase.hpp"

#include "book.hpp"
#include "gtest/gtest.h"

TEST(BookDatabaseSize, ReturnsSize) {
  BookDatabase& database = BookDatabase::instance();

  EXPECT_EQ(database.size(), 210);
}

TEST(BookDatabaseFind, ReturnsNullptrForBookNotInDatabase) {
  BookDatabase& database = BookDatabase::instance();
  EXPECT_TRUE(database.find("123XYZ789") == nullptr);
}

TEST(BookDatabaseFind, ReturnsPointerForBookInDatabase) {
  BookDatabase& database = BookDatabase::instance();
  Book* book_ptr = database.find("0001034359");
  EXPECT_TRUE(book_ptr != nullptr);
  Book expected_book = Book(
      "Tales of Hans Christian Andersen ; \n"
          "                     read by Michael Redgrave. (1st edition)",
      "Hans Christian Andersen", "0001034359", 99.92);
  EXPECT_EQ(*book_ptr, expected_book);
}

TEST(BookDatabaseFind, PointerIsConsistent) {
  BookDatabase& database = BookDatabase::instance();
  Book* book_ptr_one = database.find("0001034359");
  Book* book_ptr_two = database.find("0001034359");
  EXPECT_TRUE(book_ptr_one != nullptr);
  EXPECT_TRUE(book_ptr_two != nullptr);
  EXPECT_EQ(book_ptr_one, book_ptr_two);
}
