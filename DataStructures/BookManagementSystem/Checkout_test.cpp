// Unit tests for the Checkout class.

#include "Checkout.hpp"

#include "book.hpp"
#include "BookDatabase.hpp"
#include "gtest/gtest.h"

TEST(CheckoutTestShopForBooks, Unused) {
  Checkout checkout;
  checkout.shop_for_books();

  ASSERT_EQ(checkout.my_cart().size(), 5);

  std::vector<Book> books = {
      Book("Like the Animals", "", "9780895656926", 0.0),
      Book("131 Answer Key", "", "54782169785", 0.0),
      Book("Les Mis", "", "0140444300", 0.0),
      Book("Eat pray love", "", "9780399576775", 0.0),
      Book("Hunger Games", "", "9780545310581", 0.0),
  };
  std::vector<Book>::iterator iter = books.begin();

  std::stack<Book> copy = checkout.my_cart();
  while (!copy.empty() && iter != books.end()) {
    EXPECT_EQ(copy.top(), *iter);
    copy.pop();
    iter++;
  }

  EXPECT_TRUE(copy.empty());
  EXPECT_EQ(iter, books.end());
}

TEST(CheckoutTestSwitchCarts, Unused) {
  Checkout checkout;
  checkout.shop_for_books();
  checkout.switch_carts();

  ASSERT_EQ(checkout.working_cart().size(), 5);

  std::vector<Book> books = {
      Book("Like the Animals", "", "9780895656926", 0.0),
      Book("131 Answer Key", "", "54782169785", 0.0),
      Book("Les Mis", "", "0140444300", 0.0),
      Book("Eat pray love", "", "9780399576775", 0.0),
      Book("Hunger Games", "", "9780545310581", 0.0),
  };
  std::vector<Book>::iterator iter = books.begin();

  std::stack<Book> copy = checkout.working_cart();
  while (!copy.empty() && iter != books.end()) {
    EXPECT_EQ(copy.top(), *iter);
    copy.pop();
    iter++;
  }

  EXPECT_TRUE(copy.empty());
  EXPECT_EQ(iter, books.end());
}

TEST(CheckoutTestMoveBooksToCheckout, Unused) {
  Checkout checkout;
  checkout.shop_for_books();
  checkout.switch_carts();
  checkout.move_books_to_checkout();

  ASSERT_EQ(checkout.checkout_counter().size(), 5);

  std::vector<Book> books = {
      Book("Like the Animals", "", "9780895656926", 0.0),
      Book("131 Answer Key", "", "54782169785", 0.0),
      Book("Les Mis", "", "0140444300", 0.0),
      Book("Eat pray love", "", "9780399576775", 0.0),
      Book("Hunger Games", "", "9780545310581", 0.0),
  };
  std::vector<Book>::iterator iter = books.begin();

  std::queue<Book> copy = checkout.checkout_counter();
  while (!copy.empty() && iter != books.end()) {
    EXPECT_EQ(copy.front(), *iter);
    copy.pop();
    iter++;
  }

  EXPECT_TRUE(copy.empty());
  EXPECT_EQ(iter, books.end());
}

TEST(CheckoutTestDoCheckout, Unused) {
  Checkout checkout;
  checkout.shop_for_books();
  checkout.switch_carts();
  checkout.move_books_to_checkout();
  checkout.do_checkout();

  EXPECT_DOUBLE_EQ(checkout.amount_due(), 238.48);
}
