# C++ skeleton for Bison

# Copyright (C) 2002-2015 Free Software Foundation, Inc.

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

m4_pushdef([b4_copyright_years],
           [2002-2015])

# b4_stack_define
# ---------------
m4_define([b4_stack_define],
[[  /// A stack with random access from its top.
  template <class T, class S = std::vector<T> >
  class stack
  {
  public:
    // Hide our reversed order.
    typedef typename S::reverse_iterator iterator;
    typedef typename S::const_reverse_iterator const_iterator;

    stack ()
      : seq_ ()
    {
      seq_.reserve (200);
    }

    stack (unsigned n)
      : seq_ (n)
    {}

    /// Random access.
    ///
    /// Index 0 returns the topmost element.
    T&
    operator[] (unsigned i)
    {
      return seq_[seq_.size () - 1 - i];
    }

    /// Random access.
    ///
    /// Index 0 returns the topmost element.
    const T&
    operator[] (unsigned i) const
    {
      return seq_[seq_.size () - 1 - i];
    }

    /// Steal the contents of \a t.
    ///
    /// Close to move-semantics.
    void
    push (T& t)
    {
      seq_.push_back (T());
      operator[](0).move (t);
    }

    void
    pop (unsigned n = 1)
    {
      for (; n; --n)
        seq_.pop_back ();
    }

    void
    clear ()
    {
      seq_.clear ();
    }

    typename S::size_type
    size () const
    {
      return seq_.size ();
    }

    const_iterator
    begin () const
    {
      return seq_.rbegin ();
    }

    const_iterator
    end () const
    {
      return seq_.rend ();
    }

  private:
    stack (const stack&);
    stack& operator= (const stack&);
    /// The wrapped container.
    S seq_;
  };

  /// Present a slice of the top of a stack.
  template <class T, class S = stack<T> >
  class slice
  {
  public:
    slice (const S& stack, unsigned range)
      : stack_ (stack)
      , range_ (range)
    {}

    const T&
    operator [] (unsigned i) const
    {
      return stack_[range_ - i];
    }

  private:
    const S& stack_;
    unsigned range_;
  };
]])

b4_defines_if(
[b4_output_begin([b4_dir_prefix[]stack.hh])
b4_copyright([Stack handling for Bison parsers in C++])[

/**
 ** \file ]b4_dir_prefix[stack.hh
 ** Define the ]b4_namespace_ref[::stack class.
 */

]b4_cpp_guard_open([b4_dir_prefix[]stack.hh])[

# include <vector>

]b4_namespace_open[
]b4_stack_define[
]b4_namespace_close[

]b4_cpp_guard_close([b4_dir_prefix[]stack.hh])
b4_output_end()
])

m4_popdef([b4_copyright_years])
