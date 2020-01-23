#include <vector>
#include <H5Cpp.h>

enum class Vowel : unsigned {A, E, I, O, U};

int main()
{
	// File
	std::string fileName = "from_cpp.h5";
	H5::H5File file(fileName, H5F_ACC_TRUNC);
	
	{ // File attribute
		H5std_string  attrName  = "name";
		H5std_string  attrData  = "test file";
		const hsize_t dims[]    = {1};

		H5::StrType dtype(H5::PredType::C_S1);
		dtype.setCset(H5T_CSET_UTF8);
		dtype.setSize(H5T_VARIABLE);
		H5::DataSpace dataspace(H5S_SCALAR);
		H5::Attribute attribute = file.createAttribute(attrName, dtype, dataspace);
		attribute.write(dtype, attrData); 
		attribute.close();
		dataspace.close();
	}

	// Writing string attribute with fixed size
	// 
	// H5::AtomType dtype(H5::PredType::C_S1);
	// dtype.setSize(attrData.size()*sizeof(char));
	// H5::DataSpace dataspace(1, dims);
	// H5::Attribute attribute = file.createAttribute(attrName, dtype, dataspace);
	// attribute.write(dtype, attrData); 
	// attribute.close();
	// dataspace.close();

	// Group
	H5::Group group = file.createGroup("group example");

	{ // Group attribute
		H5std_string  attrName  = "number";
		int           attrData  = 3;
		const hsize_t dims[]    = {1};

		H5::DataType dtype(H5::PredType::NATIVE_INT);
		H5::DataSpace dataspace(1, dims);
		H5::Attribute attribute = group.createAttribute(attrName, dtype, dataspace);
		attribute.write(dtype, &attrData); 
		attribute.close();
		dataspace.close();
	}

	{ // Group dataset
		H5std_string  datasetName = "simple vector";
		std::vector<int> datasetData = {0, 1, 2};
		const hsize_t dims[]    = {3};

		H5::DataType dtype(H5::PredType::NATIVE_INT);
		H5::DataSpace dataspace(1, dims);
		H5::DataSet dataset = group.createDataSet(datasetName, dtype, dataspace);
		dataset.write(datasetData.data(), H5::PredType::NATIVE_INT);
		dtype.close();
		dataspace.close();
		dataset.close();
	}

	{ // File dataset
		H5std_string  datasetName = "complex vector";
		std::vector<int> datasetData = {0, 1, 2, 0, 10, 20};
		const hsize_t dims[]    = {2, 3};

		H5::DataType dtype(H5::PredType::NATIVE_INT);
		H5::DataSpace dataspace(2, dims);
		H5::DataSet dataset = file.createDataSet(datasetName, dtype, dataspace);
		dataset.write(datasetData.data(), H5::PredType::NATIVE_INT);
		dtype.close();
		dataspace.close();
		dataset.close();
	}

	// Group with hard link
	H5::Group groupHL = file.createGroup("something inside");
	groupHL.link(H5L_TYPE_HARD, "/group example", "group with things");

	{ 
		// Enum dataset
		H5std_string  datasetName = "enumeration";
		std::vector<Vowel> datasetData = {Vowel::I, Vowel::E, Vowel::U, Vowel::A, Vowel::O};
		const hsize_t dims[]    = {datasetData.size()};

		H5::DataType fileType(H5::PredType::STD_U32LE);
		H5::DataType memType (H5::PredType::NATIVE_UINT);
		H5::DataSpace dataspace(1, dims);
		H5::DataSet dataset = file.createDataSet(datasetName, fileType, dataspace);
		dataset.write(datasetData.data(), memType);
		fileType.close();
		memType.close();
		dataspace.close();
		dataset.close();
	}

	groupHL.close();
	group.close();
	file.close();
	return 0;
}
