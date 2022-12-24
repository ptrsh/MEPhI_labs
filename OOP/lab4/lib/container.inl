template <typename T>
myVector<T>::myVector(int length) : mLength{length} {
        assert(length >= 0);
        if (length > 0)
            mData = new T[length] {};
}

template <typename T> 
myVector<T>::~myVector() {
	delete[] mData;
}

template <typename T>
void myVector<T>::erase() {
	delete[] mData;
	mData = nullptr;
    mLength = 0;
}

template <typename T>
T& myVector<T>::operator[](int index) {
	assert(index >= 0 && index < mLength);
	return mData[index];
}

template <typename T>
void myVector<T>::reallocate(int newLength) {
	erase();
	
	if (newLength <= 0)
		return;
	
	mData = new T[newLength];
    mLength = newLength;
}

template <typename T>
void myVector<T>::resize(int newLength) {
	if (newLength == mLength)
		return;

	if (newLength <= 0) {
		erase();
		return;
	}

	T *data{new T[newLength]};
	
	if (mLength > 0) {
		int elementsToCopy{(newLength > mLength) ? mLength : newLength};

		for (int index = 0; index < elementsToCopy; ++index)
			data[index] = mData[index];
	}

	delete[] mData;

	mData = data;
    mLength = newLength;
}

template <typename T>
void myVector<T>::insertBefore(T value, int index) {
	assert(index >= 0 && index <= mLength);

	T* data {new T[mLength+1] };
	
	for (int before = 0; before < index; ++before)
		data[before] = mData[before];

	data[index] = value;
	
	for (int after = index; after < mLength; ++after)
		data[after+1] = mData[after];

	delete[] mData;
	mData = data;
	++mLength;
}

template <typename T>
void myVector<T>::remove(int index) {
        assert(index >= 0 && index < mLength);
 
        if (mLength == 1) {
            erase();
            return;
        }
 
		int *data{new T[mLength-1]};
 
        for (int before = 0; before < index; ++before)
            data[before] = mData[before];
 
        for (int after = index + 1; after < mLength; ++after)
            data[after-1] = mData[after];

        delete[] mData;
        mData = data;
        --mLength;
    }
	
template <typename T> 
void myVector<T>::insertAtBeginning(T value) {insertBefore(value, 0);}

template <typename T>
void myVector<T>::push_back(T value) {insertBefore(value, mLength);}

template <typename T>
int myVector<T>::size() const {return mLength;}
