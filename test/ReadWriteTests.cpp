//!
//! @file 			ReadWriteTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2014/04/07
//! @last-modified 	2014/05/07
//! @brief 			Contains basic tests.
//! @details
//!					See README.rst in root dir for more info.

#include <iostream>
#include <fstream>
#include <cstdint>

#include "../api/CsvCpp.hpp"

#include "../lib/UnitTest++/src/UnitTest++.h"

namespace CsvCppTest
{
	SUITE(ReadWriteTests)
	{

		TEST(BasicReadWriteTest)
		{
			// Connect up error and debug streams
			CsvCpp::debugMsg.buff = &std::cout;
			CsvCpp::errorMsg.buff = &std::cout;

			std::ofstream myfile;
			myfile.open("test/test.csv");
			myfile << "element11,element12\nelement21,element22";
			myfile.close();

			CsvCpp::Parser csvParser;
			csvParser.SetFilename("test/test.csv");
			csvParser.recordDelimiter = "\n";

			// Read back the entire file, file not exist, so within try/catch
			CsvCpp::CsvTable csvTable;
			try
			{
				csvTable = csvParser.ReadEntireFile();
				remove("test/test.csv");
			}
			catch(std::exception& e)
			{
				std::cout << e.what();
				// Something bad happened
				CHECK(false);
				return;
			}

			CHECK_EQUAL("element11", csvTable[0][0]);
			CHECK_EQUAL("element12", csvTable[0][1]);
			CHECK_EQUAL("element21", csvTable[1][0]);
			CHECK_EQUAL("element22", csvTable[1][1]);

			// Print out the CSV table for debug info
			uint32_t x, y;

			for(x = 0; x < csvTable.NumRecords(); x++)
			{
				for(y = 0; y < csvTable[x].NumFields(); y++)
				{
					std::cout << "csvTable[" << x << "][" << y << "] = " << csvTable[x][y] << std::endl;

				}
			}

		}
		
		TEST(LfAtEndOfFileReadWriteTest)
		{
			// Connect up error and debug streams
			CsvCpp::debugMsg.buff = &std::cout;
			CsvCpp::errorMsg.buff = &std::cout;

			std::ofstream myfile;
			myfile.open ("test/test.csv");
			myfile << "element11,element12\nelement21,element22\n";
			myfile.close();

			CsvCpp::Parser csvParser;
			csvParser.SetFilename("test/test.csv");
			csvParser.recordDelimiter = "\n";

			// Read back the entire file, file not exist, so within try/catch
			CsvCpp::CsvTable csvTable;
			try
			{
				csvTable = csvParser.ReadEntireFile();
				remove("test/test.csv");
			}
			catch(std::exception& e)
			{
				std::cout << e.what();
				// Something bad happened
				CHECK(false);
				return;
			}

			CHECK_EQUAL("element11", csvTable[0][0]);
			CHECK_EQUAL("element12", csvTable[0][1]);
			CHECK_EQUAL("element21", csvTable[1][0]);
			CHECK_EQUAL("element22", csvTable[1][1]);
			CHECK_EQUAL(2, csvTable.NumRecords());

		}

		TEST(CrLfAtEndOfRowsReadWriteTest)
		{
			// Connect up error and debug streams
			CsvCpp::debugMsg.buff = &std::cout;
			CsvCpp::errorMsg.buff = &std::cout;

			std::ofstream myfile;
			myfile.open ("test/test.csv");
			myfile << "element11,element12\r\nelement21,element22\r\n";
			myfile.close();

			CsvCpp::Parser csvParser;
			csvParser.SetFilename("test/test.csv");
			csvParser.recordDelimiter = "\r\n";

			// Read back the entire file, file not exist, so within try/catch
			CsvCpp::CsvTable csvTable;
			try
			{
				csvTable = csvParser.ReadEntireFile();
				remove("test/test.csv");
			}
			catch(std::exception& e)
			{
				std::cout << e.what();
				// Something bad happened
				CHECK(false);
				return;
			}

			CHECK_EQUAL("element11", csvTable[0][0]);
			CHECK_EQUAL("element12", csvTable[0][1]);
			CHECK_EQUAL("element21", csvTable[1][0]);
			CHECK_EQUAL("element22", csvTable[1][1]);
			CHECK_EQUAL(2, csvTable.NumRecords());

		}

	} // SUITE(ReadWriteTests)
} // namespace CsvCppTest
