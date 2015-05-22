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

	void detach();
	void attach(Intermediary* other);
};

template<typename T> SmartPointer<T>::SmartPointer(T* res){
	data = new Intermediary;
	data->resource = res;
	data->refCount = 1;
}

template<typename T> SmartPointer<T>::~SmartPointer(){
	detach();
}

template<typename T> T& SmartPointer<T>::operator*() const{
	return *data->resource;
}

template<typename T> T* SmartPointer<T>::operator->() const{
	return data->resource;
}

template<typename T> void SmartPointer<T>::detach(){
	--data->refCount;
	if(data->refCount == 0){
		delete data->resource;
		delete data;
	}
}

template<typename T> void SmartPointer<T>::attach(Intermediary* other){
	data = other;
	++ data->refCount;
}

template<typename T> SmartPointer<T>::SmartPointer(const SmartPointer& other){
	attach(other.data);
}

template<typename T> SmartPointer<T>& SmartPointer<T>::operator=(const SmartPointer& other){
	if(this != &other){
		detach();
		attach(other.data);
	}
	return *this;
}