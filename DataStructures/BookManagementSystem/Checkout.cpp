#include "Checkout.hpp"

#include <iomanip>
#include <map>
#include <queue>
#include <stack>

#include "book.hpp"

namespace {

constexpr bool kOutputTrace = true;

// Call this function from within the carefully_move_books functions, just
// before kicking off the recursion and then just after each move.
void trace(
    std::stack<Book> const & sourceCart,
    std::stack<Book> const & destinationCart,
    std::stack<Book> const & spareCart,
    std::ostream & s = std::clog) {
  // Count and label the number of moves
  static std::size_t move_number = 0;

  // First time called will bind parameters to copies
  static std::map<std::stack<Book> const *, std::stack<Book>> book_carts = {
     { &sourceCart, {} },
     { &destinationCart, {} },
     { &spareCart, {} }
  };
  static std::map<std::stack<Book> const *, std::string> col_labels = {
      { &sourceCart, "Broken Cart" },
      { &destinationCart, "Working Cart" },
      { &spareCart, "Spare Cart" }
  };

  // Interrogating the stacks is a destructive process, so local copies of the
  // parameters are made to work with. The CarefullyMoveBooks algorithm will
  // swap the order of the arguments passed to this functions, but they will
  // always be the same objects - just in different orders.
  //
  // When outputting the stack contents, keep the original order so we humans
  // can trace the movements easier. A container (std::map) indexed by the
  // object's identity (address) is created so the canonical order remains the
  // same from one invocation to the next.
  book_carts[&sourceCart] = sourceCart;
  book_carts[&destinationCart] = destinationCart;
  book_carts[&spareCart] = spareCart;


  // Determine the size of the tallest stack.
  std::size_t tallest_stack_size = 0;
  for (auto& book_cart : book_carts) {
    if (book_cart.second.size() > tallest_stack_size) {
      tallest_stack_size = book_cart.second.size();
    }
  }

  if (kOutputTrace) {
    // Print the header
    s << "After " << std::setw( 3 ) << move_number++ << " moves:     " << std::left;      // print the move number
    for (const auto& col_label : col_labels) {
       s << std::setw( 23 ) << col_label.second;
    }
    s << std::right << "\n                     " << std::string( 23*3, '-' ) << '\n';     // underline the labels

    // Print the stack's contents.
    for (; tallest_stack_size > 0;  --tallest_stack_size) {
      s << std::string( 21, ' ' );

      for (auto& book_cart : book_carts) {
        if (book_cart.second.size() == tallest_stack_size) {
          std::string title = book_cart.second.top().title();
          if (title.size() > 20) {
            title[17] = title[18] = title[19] = '.';               // replace last few characters of long titles with "..."
          }
          s << std::left << std::setw( 23 ) << title.substr( 0, 20 ) << std::right;
          book_cart.second.pop();
        } else {
          s << std::string( 23, ' ' );
        }
      }
      s << '\n';
    }
    s << "                     " << std::string( 69, '=' ) << "\n\n\n\n";
  }
}

}  // namespace

Checkout::Checkout() : _book_database( BookDatabase::instance() ) {}

/*
 * A recursive algorithm to carefully move books from a broken cart to a working
 * cart is given as follows:
 *   START
 *   Procedure carefully_move_books (
 *       number_of_books_to_be_moved, broken_cart, working_cart, spare_cart)
 *
 *    IF number_of_books_to_be_moved == 1, THEN
 *       move top book from broken_cart to working_cart
 *       trace the move
 *
 *    ELSE
 *       carefully_move_books (
 *           number_of_books_to_be_moved-1, broken_cart, spare_cart,
 *           working_cart)
 *       move top book from broken_cart to working_cart
 *       trace the move
 *       carefully_move_books (
 *           number_of_books_to_be_moved-1, spare_cart, working_cart,
 *           broken_cart)
 *
 *    END IF
 *
 * END Procedure
 * STOP
 *
 * As a side note, the efficiency class of this algorithm is exponential.
 * That is, the Big-O is O(2^n).
 */
void Checkout::carefully_move_books(
    std::size_t quantity, std::stack<Book> & broken_cart,
    std::stack<Book> & working_cart, std::stack<Book> & spare_cart) {
    /// Implement the algorithm above.
  if(quantity == 1)
  {
    working_cart.push(broken_cart.top());
    broken_cart.pop();
    trace(broken_cart, working_cart, spare_cart);
  }
  else
  {
    carefully_move_books(quantity - 1, broken_cart, spare_cart, working_cart);
    working_cart.push(broken_cart.top());
    broken_cart.pop();
    trace(broken_cart, working_cart, spare_cart);

    carefully_move_books(quantity - 1, spare_cart, working_cart, broken_cart);
  }
}

void Checkout::shop_for_books() {
    /// Put the following books into your cart with the heaviest book on the
    /// bottom and the lightest book on the top according to the ordering given
    /// in the table below. The author should be left empty. The price should
    /// not be specified (it will be retrieved from the database later).
    ///
    ///      ISBN             Title
    ///      --------------   ----------------
    ///      9780895656926    Like the Animals        <=== lightest book
    ///      54782169785      131 Answer Key
    ///      0140444300       Les Mis
    ///      9780399576775    Eat pray love
    ///      9780545310581    Hunger Games            <===  heaviest book
  _my_cart.push(Book("Hunger Games", "", "9780545310581", 0.0));
  _my_cart.push(Book("Eat pray love", "", "9780399576775", 0.0));
  _my_cart.push(Book("Les Mis", "", "0140444300", 0.0));
  _my_cart.push(Book("131 Answer Key", "", "54782169785", 0.0));
  _my_cart.push(Book("Like the Animals", "", "9780895656926", 0.0));
}

void Checkout::switch_carts() {
    /// Carefully move the books in your now broken cart to this working cart by
    /// calling the CarefullyMoveBooks function.
  std::stack<Book> _spare_cart;
  carefully_move_books(_my_cart.size(), _my_cart, _working_cart, _spare_cart);

}

void Checkout::move_books_to_checkout() {
    /// Remove the books from your working cart and place them on the checkout
    /// counter, i.e., put them in this checkoutCounter queue.

  //Cannot use _my_cart, pop() was used in broken_cart.pop()
  //similarly, _working_cart.push(my_cart) was used and so we use the working_cart here
  for(int books_left = _working_cart.size(); books_left > 0; books_left--)
  {
    _checkout_counter.push(_working_cart.top());
    _working_cart.pop();
  }
}

void Checkout::do_checkout() {
    /// For each book in the checkout counter queue, find the book by ISBN in
    /// the store's database.  If the book on the counter is found in the
    /// database then accumulate the amount due and print the book's full
    /// description and price on the receipt (i.e. write the book's full
    /// description and price to standard output).  Otherwise, print a message
    /// on the receipt that a description and price for the book wasn't found
    /// and there will be no charge.
  for(int i = _checkout_counter.size(); i > 0; i--)
  {
    //Book * book
    auto book = _book_database.find(_checkout_counter.front().isbn());
    if( book != nullptr)//book is found!
    {
      _amount_due += book->price();
      std::cout << *book;
    }
    else//book is not found, cannot use book->isbn() or title()
    {
      std::cout << std::quoted(_checkout_counter.front().isbn()) << ", ("
        << _checkout_counter.front().title() << "), " << "is Free!!" << std::endl;
    }
    _checkout_counter.pop();
  }
  std::cout << std::string(25, '=') << std::endl;
  std::cout << "Total: $" << _amount_due << std::endl;
}

std::stack<Book> Checkout::my_cart() const {
  return _my_cart;
}

std::stack<Book> Checkout::working_cart() const {
  return _working_cart;
}

std::queue<Book> Checkout::checkout_counter() const {
  return _checkout_counter;
}

double Checkout::amount_due() const {
  return _amount_due;
}
