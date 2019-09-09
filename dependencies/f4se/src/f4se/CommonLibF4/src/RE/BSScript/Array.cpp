#include "RE/BSScript/Array.h"

#include "f4se/PapyrusValue.h"  // VMValue::ArrayData


namespace RE
{
	namespace BSScript
	{
		Array::~Array()
		{
			dtor();
		}


		[[nodiscard]] auto Array::at(size_type a_pos)
			-> reference
		{
			if (a_pos >= size()) {
				out_of_range(__FUNCTION__, a_pos);
			}

			return _arr.data()[a_pos];
		}


		[[nodiscard]] auto Array::operator[](size_type a_pos)
			-> reference
		{
			return _arr[a_pos];
		}




		[[nodiscard]] auto Array::front()
			-> reference
		{
			return _arr.front();
		}


		[[nodiscard]] auto Array::back()
			-> reference
		{
			return _arr.back();
		}



		[[nodiscard]] Variable* Array::data() noexcept
		{
			return _arr.data();
		}


		[[nodiscard]] auto Array::begin() noexcept
			-> iterator
		{
			return _arr.begin();
		}


		[[nodiscard]] auto Array::begin() const noexcept
			-> const_iterator
		{
			return _arr.begin();
		}


		[[nodiscard]] auto Array::cbegin() const noexcept
			-> const_iterator
		{
			return begin();
		}


		[[nodiscard]] auto Array::end() noexcept
			-> iterator
		{
			return _arr.end();
		}


		[[nodiscard]] auto Array::end() const noexcept
			-> const_iterator
		{
			return _arr.end();
		}


		[[nodiscard]] auto Array::cend() const noexcept
			-> const_iterator
		{
			return end();
		}


		[[nodiscard]] auto Array::rbegin() noexcept
			-> reverse_iterator
		{
			return reverse_iterator(end());
		}


		[[nodiscard]] auto Array::rbegin() const noexcept
			-> const_reverse_iterator
		{
			return const_reverse_iterator(end());
		}


		[[nodiscard]] auto Array::crbegin() const noexcept
			-> const_reverse_iterator
		{
			return rbegin();
		}


		[[nodiscard]] auto Array::rend() noexcept
			-> reverse_iterator
		{
			return reverse_iterator(begin());
		}


		[[nodiscard]] auto Array::rend() const noexcept
			-> const_reverse_iterator
		{
			return const_reverse_iterator(begin());
		}


		[[nodiscard]] auto Array::crend() const noexcept
			-> const_reverse_iterator
		{
			return rend();
		}


		[[nodiscard]] const Variable* Array::data() const noexcept
		{
			return _arr.data();
		}


		[[nodiscard]] bool Array::empty() const noexcept
		{
			return _arr.empty();
		}


		[[nodiscard]] auto Array::size() const noexcept
			-> size_type
		{
			return _arr.size();
		}


		[[nodiscard]] auto Array::max_size() const noexcept
			-> size_type
		{
			return kMaxSize;
		}


		[[nodiscard]] Type& Array::type()
		{
			return _type;
		}


		[[nodiscard]] const Type& Array::type() const
		{
			return _type;
		}


		[[nodiscard]] VMTypeID Array::type_id() const
		{
			// TODO: Struct and variable
			auto typeID = _type.GetTypeID();
			switch (typeID) {
			case VMTypeID::kNone:
			case VMTypeID::kObject:
			case VMTypeID::kString:
			case VMTypeID::kInt:
			case VMTypeID::kFloat:
			case VMTypeID::kBool:
			case VMTypeID::kVariable:
				return typeID + VMTypeID::kArrayOffset;
			default:
				return typeID + VMTypeID::kObject;
			}
		}


		void Array::dtor()
		{
			using func_t = function_type_t<decltype(&Array::dtor)>;
			func_t* func = EXTRACT_F4SE_MEMBER_FN_ADDR(::VMValue::ArrayData, Destroy, func_t*);
			return func(this);
		}


		void Array::out_of_range(const char* a_fnName, size_type a_pos) const
		{
			std::string err = a_fnName;
			err += ": a_pos (which is ";
			err += std::to_string(a_pos);
			err += ") >= _len (which is ";
			err += std::to_string(_arr.size());
			err += ")";
			throw std::out_of_range(err);
		}
	}
}
