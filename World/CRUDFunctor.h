#ifndef CRUD_FUNCTOR_H
#define CRUD_FUNCTOR_H

template<class C, typename O, typename I> class ICRUDFunctor {
public:
	typedef C Container_t;
	typedef O Object_t;
	typedef I Index_t;
public:
	virtual bool create(Object_t& objectToAdd) = 0;
	virtual bool read(const Index_t& index, Object_t& outData)const = 0;
	virtual bool update(const Index_t& index, Object_t& newData) = 0;
	virtual bool del(const Index_t& index) = 0;
};

template<class Container_t, typename Object_t, typename Index_t> class CRUDFunctor: public ICRUDFunctor<Container_t, Object_t, Index_t> {
protected:
	CRUDFunctor(Container_t& container) 
		: m_container(container)
	{
	}

public:
	virtual bool create(Object_t& objectToAdd) = 0;
	virtual bool read(const Index_t& index, Object_t& outData)const = 0;
	virtual bool update(const Index_t& index, Object_t& newData) = 0;
	virtual bool del(const Index_t& index) = 0;

protected:
	Container_t& m_container;
};


#endif