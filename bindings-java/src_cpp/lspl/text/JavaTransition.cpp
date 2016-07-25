#include "JavaTransition.h"
#include "JavaLoop.h"
#include "JavaLoopIteration.h"
#include "JavaMatch.h"
#include "JavaToken.h"
#include "JavaWord.h"

#include "java/JavaText.h"

#include "lspl/java/Utils.h"
#include "lspl/java/JavaPattern.h"

#include "lspl/patterns/Pattern.h"

#include "lspl/base/Exception.h"
#include "lspl/text/Transition.h"
#include "lspl/text/markup/Word.h"
#include "lspl/text/Match.h"
#include "lspl/text/markup/Token.h"
#include "lspl/text/Node.h"
#include "lspl/text/Text.h"

#include <iostream>

using lspl::java::out;

using lspl::patterns::Pattern;

using lspl::text::Text;
using lspl::text::Transition;
using lspl::text::markup::Token;
using lspl::text::markup::Word;
using lspl::text::Match;

namespace lspl { namespace text {

jclass JavaTransition::transitionClazz;
jmethodID JavaTransition::transitionConstructor;
jfieldID JavaTransition::transitionIdField;

std::vector<JavaTransition *> JavaTransition::transitions;

JavaTransition * JavaTransition::create( Transition * transition, JNIEnv * env ) {
	switch ( transition->type ) {
	case Transition::WORD:
		return new JavaWord( transition, env );
	case Transition::MATCH:
		return new JavaMatch( transition, env );
	case Transition::TOKEN:
		return new JavaToken( transition, env );
	case Transition::LOOP:
		return new JavaLoop( transition, env );
	case Transition::ITERATION:
		return new JavaLoopIteration( transition, env );
	default:
		throw lspl::base::Exception( "Unknown pattern type", __FILE__, __LINE__ );
	}
}

JavaTransition::~JavaTransition() {
}

JavaTransition * JavaTransition::get( JNIEnv * env, jobject obj ) {
	jint id = env->GetIntField( obj, transitionIdField );
	JavaTransition *jt = transitions.at( id );
	if (!jt){
		throw std::runtime_error("Cound't find transition with id" + std::to_string(id));
	}
	return jt;
}

JavaTransition * JavaTransition::get( JNIEnv * env, const Transition * transition ) {
	if ( transitions.size() <= transition->id )
		transitions.resize( transition->id + 1 );

	JavaTransition * result = transitions[ transition->id ];

	if ( !result ) {
		result = transitions[ transition->id ] = create( const_cast<Transition*>( transition ), env );
	}

	return result;
}


void JavaTransition::init( JNIEnv * env ) {
	transitionClazz = (jclass) env->NewGlobalRef( (jobject)env->FindClass( "ru/lspl/text/Transition" ) );
	transitionIdField = env->GetFieldID( transitionClazz, "id", "I" );
	transitionConstructor = env->GetMethodID( transitionClazz, "<init>", "(ILru/lspl/text/Text;II)V" );
}

void JavaTransition::remove( JNIEnv * env, jobject obj ) {
	uint id = env->GetIntField( obj, transitionIdField );

	delete transitions.at( id );
	transitions[ id ] = 0;
}

} }
