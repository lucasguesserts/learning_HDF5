import h5py

file = h5py.File('from_python.h5', 'w')
file.attrs["name"] = "test file"

fileDataset = file.create_dataset("complex vector", data=[[0, 1, 2], [0, 10, 20]])

group = file.create_group("group example")
group.attrs["number"] = 3
groupDataset = group.create_dataset("simple vector", (1,3), dtype=int)
groupDataset[:] = [0, 1, 2]

groupSI = file.create_group("something inside") # SI: something inside
groupSI["group with things"] = group
