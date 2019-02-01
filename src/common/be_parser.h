#ifndef BE_PARSER_H_INCLUDED
#define BE_PARSER_H_INCLUDED

#include <string>
#include <iostream>
#include "LinearMath/btVector3.h"

class BeParser
{
	public:
		BeParser();
		~BeParser();

		void		trimWhitespaces(const std::string& line);
		void		removeCommentlines(std::string& line);

		bool		endMatches(const std::string& stop, std::string& line);
		bool		endMatchesStrip(const std::string& stop, std::string& line);

		bool		beginMatches(const std::string& stop, const std::string& line);
		bool		beginMatchesStrip(const std::string& stop, const std::string& line);

		std::string	returnUntillStrip(const char stop, const std::string& line);
		std::string	returnUntillStrip(const std::string& stop, const std::string& line);
		std::string	returnRemainder(const std::string& line);
		
		bool		parseUnsignedInt(const std::string& string, unsigned int& value);
		bool		parseFloat(std::string& string, float& value);
		bool		parseVector3( std::string& string, btVector3& value );
        bool        parseString(std::string& string, std::string& value );

		bool		wrap(std::string& wrapin, const std::string& towrap, const std::string& insert_front, const std::string& insert_behind );

		void		reset();
		std::string::size_type position_index;
	protected:
	private:
		std::string	m_result;

};

#endif


// #ifndef BE_PARSER_H_INCLUDED
// #define BE_PARSER_H_INCLUDED
// 
// #include <string>
// #include <iostream>
// #include "LinearMath/btVector3.h"
// 
// class BeParser
// {
// 	public:
// 		BeParser();
// 		~BeParser();
// 
// 		void		trimWhitespaces(const std::string& line);
// 		void		removeCommentlines(std::string& line);
// 
// 		bool		endMatches(const std::string& stop, std::string& line);
// 		bool		endMatchesStrip(const std::string& stop, std::string& line);
// 
// 		bool		beginMatches(const std::string& stop, const std::string& line);
// 		bool		beginMatchesStrip(const std::string& stop, const std::string& line);
// 
// 		std::string	returnUntillStrip(const char stop, const std::string& line);
// 		std::string	returnUntillStrip(const std::string& stop, const std::string& line);
// 		std::string	returnRemainder(const std::string& line);
// 		
// 		bool		parseUnsignedInt(std::string& string, unsigned int& value);
// 		bool		parseFloat(std::string& string, float& value);
// 		bool		parseVector3( std::string& string, btVector3& value );
//         bool        parseString(std::string& string, std::string& value );
// 
// 		bool		wrap(std::string& wrapin, const std::string& towrap, const std::string& insert_front, const std::string& insert_behind );
// 
// 		void		reset();
// 		std::string::size_type position_index;
// 	protected:
// 	private:
// 		std::string	m_result;
// 
// };
// 
// #endif
