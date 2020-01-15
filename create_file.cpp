#include <H5Cpp.h>

int main()
{
	// File
	std::string fileName = "from_cpp.h5";
	H5::H5File file(fileName, H5F_ACC_TRUNC);

	// File attribute
	H5std_string  attrName  = "name";
	H5std_string  attrData  = "test file";
	const hsize_t dims[]    = {1};

	H5::StrType dtype(H5::PredType::C_S1);
	dtype.setSize(H5T_VARIABLE);
	// H5::AtomType dtype(H5::PredType::C_S1);
	// dtype.setSize(attrData.size()*sizeof(char));
	H5::DataSpace dataspace(1, dims);
	H5::Attribute attribute = file.createAttribute(attrName, dtype, dataspace);
	// attribute.write(H5::PredType::C_S1, attrData); 
	attribute.write(dtype, attrData); 
	attribute.close();
	dataspace.close();

	file.close();
	return 0;
}
