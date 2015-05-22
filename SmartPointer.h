#ifndef SmartPointer_h
#define SmartPointer_h

template<typename T> class SmartPointer{
public:
	explicit SmartPointer(T* res);                                             
	SmartPointer(const SmartPointer& other);
	SmartPointer& operator=(const SmartPointer& other);
	~SmartPointer();

	T& operator*() const;
	T* operator->() const;
private:
	struct Intermediary{
		T* resource;
		size_t refCount;
	};
	Intermediary* data;
};

template<typename T> SmartPointer<T>::SmartPointer(T* res){
	data = new Intermediary;
	data->resource = res;
	data->refCount = 1;
}

template<typename T> SmartPointer<T>::~SmartPointer(){
	--data->refCount;
	if(data->refCount == 0){
		delete data->resource;
		delete data;
	}
}

template<typename T> T& SmartPointer<T>::operator*() const{
	return *data->resource;
}

template<typename T> T* SmartPointer<T>::operator->() const{
	return data->resource;
}