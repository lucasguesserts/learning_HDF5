#include <hdf5.h>
#include <string.h>

int main()
{
	herr_t status;

	/* File */
	hid_t file;
	file = H5Fcreate("from_c.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

	/* File attribute */
	hsize_t aDims[1] = {1};
	hid_t   attr, dataspace, dtype;
	char    attrName[] = "name";
	char    attrData[] = "test file";

	dtype     = H5Tcopy(H5T_C_S1);
	status    = H5Tset_size(dtype, strlen(attrData)*sizeof(char)) ;
	dataspace = H5Screate_simple(1, aDims, NULL);
	attr      = H5Acreate(file, attrName, dtype, dataspace, H5P_DEFAULT, H5P_DEFAULT);
	status    = H5Awrite(attr, dtype, attrData);
	status    = H5Tclose(dtype);
	status    = H5Sclose(dataspace);
	status    = H5Aclose(attr);

	/* Group */
	hid_t group;
	const char groupName[] = "group example";
	group = H5Gcreate(file, groupName, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

	/* Group attribute */
	char gAttrName[] = "number";
	int  gAttrData   = 3;

	dataspace = H5Screate_simple(1, aDims, NULL);
	attr      = H5Acreate(group, gAttrName, H5T_NATIVE_INT, dataspace, H5P_DEFAULT, H5P_DEFAULT);
	status    = H5Awrite(attr, H5T_NATIVE_INT, &gAttrData);
	status    = H5Sclose(dataspace);
	status    = H5Aclose(attr);

	/* Group dataset */
	hid_t   dataset;
	char    gDatasetName[] = "simple vector";
	int     gDatasetData[] = {0, 1, 2};
	hsize_t gDims[]        = {3};

	dataspace = H5Screate_simple(1, gDims, NULL);
	dataset   = H5Dcreate(group, gDatasetName, H5T_NATIVE_INT, dataspace, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	status    = H5Dwrite(dataset, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, gDatasetData);
	status    = H5Sclose(dataspace);
	status    = H5Dclose(dataset);

	/* File dataset */
	char datasetName[] = "complex vector";
	int  datasetData[] = {0, 1, 2, 0, 10, 20};
	hsize_t dims[] = {2, 3};

	dataspace = H5Screate_simple(2, dims, NULL);
	dataset   = H5Dcreate(file, datasetName, H5T_NATIVE_INT, dataspace, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	status    = H5Dwrite(dataset, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, datasetData);
	status    = H5Sclose(dataspace);
	status    = H5Dclose(dataset);

	/* Group with hard link */
	hid_t groupHL;
	const char groupHLname[] = "something inside";
	groupHL   = H5Gcreate(file, groupHLname, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

	/* Hard link within group */
	const char hardLinkName[] = "group with things";
	status    = H5Lcreate_hard(group, ".", groupHL, hardLinkName, H5P_DEFAULT, H5P_DEFAULT);

	status = H5Gclose(groupHL);
	status = H5Gclose(group);
	status = H5Fclose(file);
	return 0;
}
