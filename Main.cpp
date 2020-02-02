// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
// This program compresses a given file using run length encoding. 
// Then, the file is decompressed and compared with the original to test the compression has worked.

#include <iostream>
#include <fstream>
#include <string>

enum class RunLengthEncodeType { NON_NUMBER, NUMBER };

float RunLengthEncode_LETTER(std::string decompressedFileName);
float RunLengthEncode_NUMBER(std::string decompressedFileName);

int RunLengthDecode_NON_NUMBER(std::string compressedFileName);
int RunLengthDecode_NUMBER(std::string compressedFileName);

std::string GetCompressedFileName_NON_NUMBER(std::string decompressedFileName);
std::string GetCompressedFileName_NUMBER(std::string decompressedFileName);

std::string GetDecompressedFileName_NON_NUMBER(std::string compressedFileName);
std::string GetDecompressedFileName_NUMBER(std::string compressedFileName);


int main()
{
	std::string originalDecompressedFileName;
	RunLengthEncodeType encodeType;

	std::cout << "Type the file directory: ";
	std::getline(std::cin, originalDecompressedFileName);

	//originalDecompressedFileName = "TextFiles/test3.txt"; // Set this to the directory of the file you wish to compress
	encodeType = RunLengthEncodeType::NUMBER; // Use NUMBER for files containing any numbers. Otherwise use NON_NUMBER

	float compressionRatio = 0;

	if (RunLengthEncodeType::NON_NUMBER == encodeType)
	{
		compressionRatio = RunLengthEncode_LETTER(originalDecompressedFileName);
	}
	else
	{
		compressionRatio = RunLengthEncode_NUMBER(originalDecompressedFileName);
	}

	std::ofstream readMeFile;
	readMeFile.open("READ_ME.txt", std::ios::app);
	if (readMeFile.is_open())
	{
		readMeFile << std::endl << "==========Program output for " << originalDecompressedFileName << "==========" << std::endl;

		if (compressionRatio > 0)
		{
			std::cout << "Compression succeeded with a compression ratio of " << compressionRatio << "." << std::endl;
			readMeFile << "Compression succeeded with a compression ratio of " << compressionRatio << "." << std::endl;

			bool decompressionSucceeded = true;
			std::string compressedFileName;
			if (RunLengthEncodeType::NON_NUMBER == encodeType)
			{
				compressedFileName = GetCompressedFileName_NON_NUMBER(originalDecompressedFileName);
				if (RunLengthDecode_NON_NUMBER(compressedFileName) < 0)
				{
					std::cout << "Decompression failed." << std::endl;
					readMeFile << "Decompression failed." << std::endl;
					decompressionSucceeded = false;
				}
			}
			else
			{
				compressedFileName = GetCompressedFileName_NUMBER(originalDecompressedFileName);
				if (RunLengthDecode_NUMBER(compressedFileName) < 0)
				{
					std::cout << "Decompression failed." << std::endl;
					readMeFile << "Decompression failed." << std::endl;
					decompressionSucceeded = false;
				}
			}

			if (decompressionSucceeded)
			{
				std::cout << "Decompression succeeded." << std::endl;
				readMeFile << "Decompression succeeded." << std::endl;

				// Test if the decompressed file matches the original
				std::ifstream originalDecompressedFile;
				originalDecompressedFile.open(originalDecompressedFileName);
				if (originalDecompressedFile.is_open())
				{
					std::ifstream newDecompressedFile;

					std::string newDecompressedFileName;
					if (RunLengthEncodeType::NON_NUMBER == encodeType)
					{
						newDecompressedFileName = GetDecompressedFileName_NON_NUMBER(compressedFileName);
					}
					else
					{
						newDecompressedFileName = GetDecompressedFileName_NUMBER(compressedFileName);
					}

					newDecompressedFile.open(newDecompressedFileName);
					if (newDecompressedFile.is_open())
					{
						std::string originalString;
						std::string newString;
						std::string tempString;

						while (!originalDecompressedFile.eof())
						{
							std::getline(originalDecompressedFile, tempString);
							originalString += tempString;
						}

						while (!newDecompressedFile.eof())
						{
							std::getline(newDecompressedFile, tempString);
							newString += tempString;
						}

						if (originalString == newString)
						{
							std::cout << "The files match." << std::endl;
							readMeFile << "The files match." << std::endl;
						}
						else
						{
							std::cout << "The files do not match." << std::endl;
							readMeFile << "The files do not match." << std::endl;
						}

						newDecompressedFile.close();
					}
					else
					{
						std::cout << "Could not open newDecompressedFile." << std::endl;
						readMeFile << "Could not open newDecompressedFile." << std::endl;
					}

					originalDecompressedFile.close();
				}
				else
				{
					std::cout << "Could not open orignialDecompressedFile." << std::endl;
					readMeFile << "Could not open orignialDecompressedFile." << std::endl;
				}
			}
		}
		else
		{
			std::cout << "Compression failed." << std::endl;
			readMeFile << "Compression failed." << std::endl;
		}

		readMeFile.close();
	}
	else
	{
		std::cout << "Could not open readMeFile." << std::endl;
	}

	std::cout << "Press enter to exit." << std::endl;
	(void)getchar();
}

std::string GetCompressedFileName_NON_NUMBER(std::string decompressedFileName)
{
	std::string compressedFileName;
	unsigned decompressedFileName_size = decompressedFileName.size();

	// Generate write file name
	for (unsigned i = 0; i < decompressedFileName_size; i++)
	{
		if ('.' == decompressedFileName[i])
		{
			for (unsigned j = 0; j < i; j++)
			{
				compressedFileName += decompressedFileName[j];
			}
			compressedFileName += "_compressedLETTER";

			// Append file type
			for (unsigned j = i; j < decompressedFileName_size; j++)
			{
				compressedFileName += decompressedFileName[j];
			}

			break;
		}
	}

	return compressedFileName;
}

std::string GetCompressedFileName_NUMBER(std::string decompressedFileName)
{
	std::string compressedFileName;
	unsigned decompressedFileName_size = decompressedFileName.size();

	// Generate write file name
	for (unsigned i = 0; i < decompressedFileName_size; i++)
	{
		if ('.' == decompressedFileName[i])
		{
			for (unsigned j = 0; j < i; j++)
			{
				compressedFileName += decompressedFileName[j];
			}
			compressedFileName += "_compressedNUMBER";

			// Append file type
			for (unsigned j = i; j < decompressedFileName_size; j++)
			{
				compressedFileName += decompressedFileName[j];
			}

			break;
		}
	}

	return compressedFileName;
}

// Returns the compression ratio after Run Length encoding the passed file.
// The compressed file will be called "passedFileName_compressed.type".
// Returns a negative value if the operation was unsuccessful.
// Only works if there are no numbers in the file.
float RunLengthEncode_LETTER(std::string decompressedFileName)
{
	float returnValue = 0;

	std::ifstream decompressedFile;
	decompressedFile.open(decompressedFileName);

	if (decompressedFile.is_open())
	{
		std::string compressedFileName = GetCompressedFileName_NON_NUMBER(decompressedFileName);

		std::ofstream compressedFile;
		compressedFile.open(compressedFileName, std::ofstream::trunc);
		if (compressedFile.is_open())
		{
			unsigned decompressedFile_size = 0;
			unsigned compressedFile_size = 0;
			while (!decompressedFile.eof())
			{
				std::string currentLine;
				std::getline(decompressedFile, currentLine);

				unsigned currentLine_size = currentLine.size();
				decompressedFile_size += currentLine_size;

				if (currentLine_size > 0)
				{
					char currentChar = currentLine[0];
					int charCount = 1;
					for (unsigned i = 1; i < currentLine_size; i++)
					{
						if (currentChar == currentLine[i])
						{
							++charCount;
						}
						else
						{
							// Write compressed version to file
							if (charCount > 1)
							{
								compressedFile << charCount;
								++compressedFile_size;
							}
							compressedFile << currentChar;
							++compressedFile_size;

							currentChar = currentLine[i];
							charCount = 1;
						}
					}

					// Write compressed version to file
					if (charCount > 1)
					{
						compressedFile << charCount;
						++compressedFile_size;
					}
					compressedFile << currentChar << '\n';
					++compressedFile_size;
				}

			}// End while(!decompressedFile.eof)

			compressedFile.close();

			returnValue = (float)decompressedFile_size / (float)compressedFile_size;
		}
		else
		{
			returnValue = -2;// Write file could not be opened.
		}

		decompressedFile.close();


	}
	else
	{
		returnValue = -1; //Read file could not be opened.
	}

	return returnValue;
}

// Returns the compression ratio after Run Length encoding the passed file.
// The compressed file will be called "passedFileName_compressed.type".
// Returns a negative value if the operation was unsuccessful.
// Only works if there are no | symbols in the file.
float RunLengthEncode_NUMBER(std::string decompressedFileName)
{
	float returnValue = 0;

	std::ifstream decompressedFile;
	decompressedFile.open(decompressedFileName);

	if (decompressedFile.is_open())
	{
		std::string compressedFileName = GetCompressedFileName_NUMBER(decompressedFileName);

		std::ofstream compressedFile;
		compressedFile.open(compressedFileName, std::ofstream::trunc);
		if (compressedFile.is_open())
		{
			unsigned decompressedFile_size = 0;
			unsigned compressedFile_size = 0;
			while (!decompressedFile.eof())
			{
				std::string currentLine;
				std::getline(decompressedFile, currentLine);

				unsigned currentLine_size = currentLine.size();
				decompressedFile_size += currentLine_size;

				if (currentLine_size > 0)
				{
					char currentChar = currentLine[0];
					unsigned charCount = 1;
					for (unsigned i = 1; i < currentLine_size; i++)
					{
						if (currentChar == currentLine[i])
						{
							++charCount;
						}
						else
						{
							// Write compressed version to file
							if (charCount >= 5)
							{
								compressedFile << '|' << charCount << '|' << currentChar;
								compressedFile_size += 4;
							}
							else
							{
								for (unsigned j = 0; j < charCount; j++)
								{
									compressedFile << currentChar;
									++compressedFile_size;
								}
							}
							currentChar = currentLine[i];
							charCount = 1;
						}
					}

					// Write compressed version to file
					if (charCount >= 5)
					{
						compressedFile << '|' << charCount << '|' << currentChar;
						compressedFile_size += 4;
					}
					else
					{
						for (unsigned j = 0; j < charCount; j++)
						{
							compressedFile << currentChar;
							++compressedFile_size;
						}
					}

					compressedFile << '\n';
				}

			}// End while(!decompressedFile.eof)

			compressedFile.close();

			returnValue = (float)decompressedFile_size / (float)compressedFile_size;
		}
		else
		{
			returnValue = -2;// Write file could not be opened.
		}

		decompressedFile.close();


	}
	else
	{
		returnValue = -1; //Read file could not be opened.
	}

	return returnValue;
}

std::string GetDecompressedFileName_NON_NUMBER(std::string compressedFileName)
{
	std::string decompressedFileName;

	// Generate write file name
	std::string key = "_compressed";
	size_t found = compressedFileName.rfind(key);
	if (found != std::string::npos)
	{
		decompressedFileName = compressedFileName;
		decompressedFileName.replace(found, key.size(), "_decompressed");
	}

	return decompressedFileName;
}

std::string GetDecompressedFileName_NUMBER(std::string compressedFileName)
{
	std::string decompressedFileName;

	// Generate write file name
	std::string key = "_compressed";
	size_t found = compressedFileName.rfind(key);
	if (found != std::string::npos)
	{
		decompressedFileName = compressedFileName;
		decompressedFileName.replace(found, key.size(), "_decompressed");
	}

	return decompressedFileName;
}


int RunLengthDecode_NON_NUMBER(std::string compressedFileName)
{
	int returnValue = 0;

	std::ifstream compressedFile;
	compressedFile.open(compressedFileName);

	if (compressedFile.is_open())
	{
		std::ofstream decompressedFile;

		std::string decompressedFileName = GetDecompressedFileName_NON_NUMBER(compressedFileName);

		decompressedFile.open(decompressedFileName, std::ios::trunc);
		if (decompressedFile.is_open())
		{
			while (!compressedFile.eof())
			{
				std::string currentLine;
				std::getline(compressedFile, currentLine);

				unsigned currentLine_size = currentLine.size();
				for (unsigned i = 0; i < currentLine_size; i++)
				{
					if (std::isdigit(currentLine[i]))
					{
						std::string charCountString;
						charCountString += currentLine[i];
						for (unsigned j = i + 1; j < currentLine_size; j++)
						{
							if (std::isdigit(currentLine[j]))
							{
								charCountString += currentLine[j];
							}
							else
							{
								i = j;
								break;// Exit for
							}
						}

						unsigned charCount = std::stoi(charCountString);
						for (unsigned j = 0; j < charCount; j++)
						{
							decompressedFile << currentLine[i];
						}
					}
					else
					{
						decompressedFile << currentLine[i];
					}
				}

				decompressedFile << std::endl;
			}// End while(!compressedFile.eof())

			decompressedFile.close();
		}
		else
		{
			returnValue = -1;
		}

		compressedFile.close();
	}
	else
	{
		returnValue = -1;// Read file could not be opened.
	}

	return returnValue;
}

int RunLengthDecode_NUMBER(std::string compressedFileName)
{
	int returnValue = 0;

	std::ifstream compressedFile;
	compressedFile.open(compressedFileName);

	if (compressedFile.is_open())
	{
		std::ofstream decompressedFile;
		std::string decompressedFileName = GetDecompressedFileName_NUMBER(compressedFileName);

		decompressedFile.open(decompressedFileName, std::ios::trunc);
		if (decompressedFile.is_open())
		{
			while (!compressedFile.eof())
			{
				std::string currentLine;
				std::getline(compressedFile, currentLine);

				unsigned currentLine_size = currentLine.size();
				for (unsigned i = 0; i < currentLine_size; i++)
				{
					if ('|' == currentLine[i])
					{
						std::string countString;
						bool secondSymbolFound = false;
						for (unsigned j = i + 1; j < currentLine_size - 1; j++)
						{
							if ('|' == currentLine[j])
							{
								i = j + 1;
								secondSymbolFound = true;
								break;
							}
							else
							{
								countString += currentLine[j];
							}
						}

						if (secondSymbolFound)
						{
							try
							{
								unsigned count = std::stoi(countString);
								for (unsigned j = 0; j < count; j++)
								{
									decompressedFile << currentLine[i];
								}
							}
							catch(std::invalid_argument ia)
							{
								return -4;// string between | symbols cannot be converted to an integer
							}
							catch (std::out_of_range oor)
							{
								return -5;// integer between | symbols is out of range
							}
						}
						else
						{
							return -3;// Only one | symbol found
						}
					}
					else
					{
						decompressedFile << currentLine[i];
					}
				}

				decompressedFile << std::endl;
			}// End while(!compressedFile.eof())

			decompressedFile.close();
		}
		else
		{
			returnValue = -1;
		}

		compressedFile.close();
	}
	else
	{
		returnValue = -1;// Read file could not be opened.
	}

	return returnValue;
}