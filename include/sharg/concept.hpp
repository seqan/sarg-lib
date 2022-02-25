// -----------------------------------------------------------------------------------------------------------
// Copyright (c) 2006-2021, Knut Reinert & Freie Universität Berlin
// Copyright (c) 2016-2021, Knut Reinert & MPI für molekulare Genetik
// This file may be used, modified and/or redistributed under the terms of the 3-clause BSD-License
// shipped with this file and also available at: https://github.com/seqan/sharg-parser/blob/master/LICENSE.md
// -----------------------------------------------------------------------------------------------------------

/*!\file
 * \author Svenja Mehringer <svenja.mehringer AT fu-berlin.de>
 * \brief Provides helper concepts.
 */

#pragma once

#include <seqan3/std/concepts>

#include <sharg/auxiliary.hpp>

namespace sharg
{

/*!\concept sharg::istreamable
 * \ingroup argument_parser
 * \brief Concept for types that can be parsed from a std::istream via the stream operator.
 * \tparam value_type The type to check whether it's stremable via std::istream.
 *
 * ### Requirements
 *
 * `std::istream` must support the (un)formatted input function (`operator>>`) for an l-value of a given `value_type`.
 */
template <typename value_type>
concept istreamable = requires (std::istream & is, value_type & val)
{
    SHARG_RETURN_TYPE_CONSTRAINT(is >> val, std::same_as, std::istream&);
};

/*!\concept sharg::argument_parser_compatible_option
 * \brief Checks whether the the type can be used in an add_(positional_)option call on the argument parser.
 * \ingroup argument_parser
 * \tparam option_type The type to check.
 *
 * ### Requirements
 *
 * In order to model this concept, the type must either model sharg::istreamable and sharg::ostreamable or
 * model sharg::named_enumeration<option_type>.
 *
 * \remark For a complete overview, take a look at \ref argument_parser
 */
template <typename option_type>
concept argument_parser_compatible_option = sharg::istreamable<option_type> || named_enumeration<option_type>;

} // namespace sharg
