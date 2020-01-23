#include <iostream>
#include <vector>
#include <H5Cpp.h>

enum class Vowel : unsigned {A, E, I, O, U};

int main()
{
	try
	{
		// File
		std::string filePath = "from_cpp.h5";
		H5::H5File file(filePath, H5F_ACC_RDONLY);
		std::cout << "File '" << filePath << "' opened." << std::endl;

		{
			// File attribute
			std::string attrName  = "name";
			H5::Attribute attribute = file.openAttribute(attrName);
			std::cout << "\tAttribute '" << attribute.getName() << "' opened." << std::endl;
			// Attribute data
			std::string attrData;
			attribute.read(attribute.getStrType(), attrData);
			std::cout << "\t\tAttribute '" << attribute.getName() << "' data read." << std::endl;
			std::cout << "\t\tContent: " << attrData << std::endl;
			attribute.close();
		}

		{
			// File dataset
			std::string datasetName = "complex vector";
			H5::DataSet dataset = file.openDataSet(datasetName);
			std::cout << "\tDataset '" << datasetName << "' opened." << std::endl;
			// Dataset data
			std::vector<int> datasetData;
			datasetData.resize(6);
			dataset.read(datasetData.data(), H5::PredType::NATIVE_INT);
			std::cout << "\t\tDataSet '" << datasetName << "' data read." << std::endl;
			std::cout << "\t\tContent: {";
			for(auto& val: datasetData)
				std::cout << val << ", ";
			std::cout << "}" << std::endl;
			dataset.close();
		}

		{ 
			// Enum dataset
			H5std_string  datasetName = "enumeration";
			H5::DataSet dataset = file.openDataSet(datasetName);
			std::cout << "\tDataset '" << datasetName << "' opened." << std::endl;
			// Dataset data
			std::vector<Vowel> datasetData;
			datasetData.resize(5);
			dataset.read(datasetData.data(), H5::PredType::NATIVE_UINT);
			std::cout << "\t\tDataSet '" << datasetName << "' data read." << std::endl;
			std::cout << "\t\tContent: {";
			for(auto& val: datasetData)
				std::cout << static_cast<unsigned>(val) << ", ";
			std::cout << "}" << std::endl;
			// Check correctness
			std::vector<Vowel> correctDatasetData = {Vowel::I, Vowel::E, Vowel::U, Vowel::A, Vowel::O};
			for(unsigned i=0 ; i<correctDatasetData.size() ; ++i)
				if(correctDatasetData.at(i) != datasetData.at(i))
					std::cout << "Error at entry" << i << std::endl;
			// Close
			dataset.close();
		}
		
		// Group
		std::string groupName = "group example";
		H5::Group group = file.openGroup(groupName);
		std::cout << "Group '" << groupName << "' opened." << std::endl;

		{
			// Group attribute
			std::string attrName  = "number";
			H5::Attribute attribute = group.openAttribute(attrName);
			std::cout << "\tAttribute '" << attribute.getName() << "' opened." << std::endl;
			// Attribute data
			int attrData;
			attribute.read(attribute.getIntType(), &attrData);
			std::cout << "\t\tAttribute '" << attribute.getName() << "' data read." << std::endl;
			std::cout << "\t\tContent: " << attrData << std::endl;
			attribute.close();
		}

		{
			// Group dataset
			std::string datasetName = "simple vector";
			H5::DataSet dataset = group.openDataSet(datasetName);
			std::cout << "\tDataset '" << datasetName << "' opened." << std::endl;
			// Dataset data
			std::vector<int> datasetData;
			datasetData.resize(3);
			dataset.read(datasetData.data(), H5::PredType::NATIVE_INT);
			std::cout << "\t\tDataSet '" << datasetName << "' data read." << std::endl;
			std::cout << "\t\tContent: {";
			for(auto& val: datasetData)
				std::cout << val << ", ";
			std::cout << "}" << std::endl;
			dataset.close();
		}

		// Close general
		group.close();
		file.close();
	}
	catch (H5::FileIException fileException)
	{
		std::cout << "File exception!" << std::endl;
		std::cout << fileException.getDetailMsg() << std::endl;
	}
	catch (H5::AttributeIException attributeException)
	{
		std::cout << "Attribute exception!" << std::endl;
		std::cout << attributeException.getDetailMsg() << std::endl;
	}
	catch (H5::GroupIException groupException)
	{
		std::cout << "Group exception!" << std::endl;
		std::cout << groupException.getDetailMsg() << std::endl;
	}
	catch (H5::DataSetIException datasetException)
	{
		std::cout << "DataSet exception!" << std::endl;
		std::cout << datasetException.getDetailMsg() << std::endl;
	}
	return 0;
}
