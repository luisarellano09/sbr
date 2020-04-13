/**
 * \file doxygen_template.h
 * \author The Author
 * \date 20 Jun 2016
 * \todo TODO for this file.
 *
 * \brief A brief description of the file
 *
 * A more detailed description can be placed here.
 * Multiple lines of description have to start with *.
 *
 * If you want to end a command, add an empty line (starting with *).
 *
 * Inside of a comment block, the user can use doxygen commands like "brief" etc..
 * A list of all available commands can be found at \see https://www.stack.nl/~dimitri/doxygen/manual/commands.html .
 *
 * You can reference to entries in the documentation by using #. Example: #myEnum_t.
 * 
 * 
 * Changes
 * 13.04.2020: Doc was created
 * 
 *
 */

#ifndef _DOXYGEN_TEMPLATE_H
#define _DOXYGEN_TEMPLATE_H

//####################### Defines/Macros
 /**
 * \brief a brief description of what the define is representing
 *
 * If needed, a more detailed description can be given below */
#define TOP_DOCUMENTED_DEFINE		0x1
#define AFTER_DOCUMENTED_DEFINE		0x2	 /**< \brief by putting a < next to the comment-start. The documentation referes to the left instead to the next line. */

//####################### Enumerations
/**
 * \brief Enumerations. Use brief, otherwise the index won't have a brief explanation.
 *
 * Detailed explaination of the enumeration.
 */
typedef enum {
  ENUM_FIRST,  /**< Some documentation first. */
  ENUM_SECOND, /**< Some documentation second. */
  ENUM_ETC     /**< Etc. */
} myEnum_t;

//####################### Structures
/**
 * \brief The purpose as well as the members of a structure have to be documented.
 *
 * Make clear what the structure is used for and what is the purpose of the members.
 *
 */
typedef struct myStruct_t {
  int a;    /**< Some documentation for the member myStruct_t#a. */
  int b;    /**< Some documentation for the member myStruct_t#b. */
  double c; /**< Etc. */
};


//####################### class
/**
 * \brief The purpose as well as the members and methos of a class have to be documented.
 *
 * Make clear what the class is used for and what is the purpose of the members and methos.
 */
class doxygen_template{


private:
	int m_a;    /**< Some documentation for the member doxygen_template#m_a. */

public:
	/**
	 * \brief Example showing how to document a function with Doxygen.
	 *
	 * Description of what the function does. This part may refer to the parameters
	 * of the function, like \p param1 or \p param2. A word of code can also be
	 * inserted like \c this which is equivalent to <tt>this</tt> and can be useful
	 * to say that the function returns a \c void or an \c int.
	 * We can also include text verbatim,
	 * \verbatim like this\endverbatim
	 * Sometimes it is also convenient to include an example of usage:
	 * \code
	 * uint32_t myFunction(uint32_t param1, myStruct_t param2);
	 * printf("something...\n");
	 * \endcode
	 * Or,
	 * \code{.py}
	 * pyval = python_func(arg1, arg2)
	 * print pyval
	 * \endcode
	 * when the language is not the one used in the current source file.
	 * By the way, <b>this is how you write bold text</b> or,
	 * if it is just one word, then you can just do \b this.
	 * \param param1 Description of the first parameter of the function.
	 * \param param2 The second one, which follows \p param1.
	 * \return Describe what the function returns.
	 * \see myStruct_t
	 * \see http://website/
	 * \note Something to note.
	 * \warning Warnings for this function.
	 * \todo A TODO for this function
	 */
	uint32_t myFunction(uint32_t param1, myStruct_t param2);

};



#endif /* _DOXYGEN_TEMPLATE_H */
