#pragma once

class String
{
	char*	_string;
	size_t	_size;
public:
	String();
	String(const char*);
	String(const String&);
	~String();
	//Conversion Constructors
	static const String convert(char);
	static const String convert(int);
	static const String convert(float);

	//Getters
	inline const char* getData() const { return _string; };
	inline size_t getLength() const { return _size - 1; };
	inline size_t getSize() const { return _size; };

	//Basic operator overloads
	String& operator--();
	String& operator=(const String& other);
	String& operator=(const char* other);
	String& operator+=(const String& other);
	String& operator+=(const char* other);
	String& operator+=(char other);

	template <class T>
	const String operator+(const T& other) const {
		String str(*this);
		str += other;
		return str;
	};

	friend const String operator+(const char* a, const String& b);

	bool operator==(const char * other) const;
	inline bool operator==(const String& other) const { return operator==(other._string); };

	bool operator>(const String& other) const;
	bool operator<(const String& other) const;
};

#define AS_CHARPTR(STRING) (String)(STRING).getData()
