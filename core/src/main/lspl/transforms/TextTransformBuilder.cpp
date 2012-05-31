
#include "../base/BaseInternal.h"

#include "TransformBuilder.h"
#include "TextTransformBuilder.h"
#include "TextTransform.h"
#include "../patterns/matchers/Matcher.h"
#include <boost/ptr_container/ptr_vector.hpp>
#include "../patterns/ParserAlt.h"
#include <boost/spirit/phoenix/binders.hpp>
#include <boost/spirit/phoenix/functions.hpp>

#include "../Namespace.h"

#include <iostream>

LSPL_REFCOUNT_CLASS( lspl::transforms::TextTransformBuilder )

using namespace phoenix;

namespace lspl { namespace transforms {

TextTransformBuilder::TextTransformBuilder(NamespaceRef space) : space( space ) {
}

TextTransform * TextTransformBuilder::build(
  const lspl::patterns::Alternative & alt,
  const std::string & source )
{
	lspl::patterns::ParserAlt pars(space);
	boost::ptr_vector<lspl::patterns::matchers::Matcher>* matchers=NULL;
	if(!boost::spirit::parse( source.c_str(), pars[ var(matchers) = arg1 ], space_p ).full) {
		std::cout<<"wrong pattern"<<std::endl;
	}

  return new TextTransform( matchers );
}


} } // namespace lspl::transforms