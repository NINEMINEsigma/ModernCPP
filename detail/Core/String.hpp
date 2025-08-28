#pragma once
#ifndef __FILE_Detail_Core_String_H
#define __FILE_Detail_Core_String_H

namespace Internal
{
	template<typename Char>
	class PrefixStringTree
	{
	public:
		PrefixStringTree<Char>* parent;
		PrefixStringTree<Char>* child_head;
		PrefixStringTree<Char>* child_end;
		PrefixStringTree<Char>* next;

		using my_string_view = std::basic_string_view<Char>;
	private:
		Char mine;
		Char* data;
		my_string_view rdata;
	public:
		my_string_view ReadValue() const
		{
			return rdata;
		}

		constexpr operator my_string_view() const
		{
			return rdata;
		}

		PrefixStringTree<Char>& PopBack()
		{
			if (parent)
				return *parent;
			return *this;
		}

	private:
		void RegetDataFromChild(PrefixStringTree<Char>* target)
		{
			auto size = this->rdata.size();
			if (data)
			{
				delete this->data;
				this->data = target->data;
			}
			this->rdata = target->rdata.substr(0, size);
			if (parent)
				parent->RegetDataFromChild(target);
		}
		PrefixStringTree<Char>* AddChild(Char ch)
		{
			auto next = child_head;
			child_head = new PrefixStringTree<Char>();
			if (next == nullptr)
			{
				child_end = child_head;
			}
			child_head->mine = ch;
			const auto size = rdata.size();
			child_head->data = new Char[size + 1];
			::strcpy_s(child_head->data, size, data);
			child_head->data[size] = ch;
			child_head->rdata = child_head->data;
			child_head->next = next;
			RegetDataFromChild(child_head);
			return child_head;
		}
		PrefixStringTree<Char>* FindChild(Char ch)
		{
			for (auto head = child_head; head; head = head->next)
			{
				if (head->mine)
					return head;
			}
			return nullptr;
		}
	public:
		PrefixStringTree<Char>& operator+(Char ch)
		{
			if (ch == 0)
				return *this;
			auto result = FindChild(ch);
			if (result)
				return *result;
			return *AddChild(ch);
		}

		PrefixStringTree<Char>& operator+(my_string_view view)
		{
			if (view.size() == 0 || view.front() == 0)
				return *this;
			return this->operator+(view.front()).operator+(view.substr(1));
		}

		bool operator==(my_string_view str)
		{
			return rdata == str;
		}
		bool operator!=(my_string_view str)
		{
			return rdata != str;
		}

		static PrefixStringTree<Char>& GetRoot()
		{
			static PrefixStringTree<Char> root;
			return root;
		}

		decltype(auto) GetSize()
		{
			return rdata.size();
		}

		PrefixStringTree<Char>& GetPrefix(size_t size = -1)
		{
			if (size >= rdata.size())
				return *this;
			return parent->GetPrefix(size);
		}

		PrefixStringTree<Char>& GetSamePrefix(PrefixStringTree<Char>& other)
		{
			if (rdata.front() != other.rdata.front())
				return GetRoot();
			auto i = 0;
			for (auto e = std::min<size_t>(rdata.size(), other, rdata.size()); i <= e; i++)
			{
				if (rdata[i] != other.rdata[i])
					break;
			}
			return this->GetPrefix(i);
		}

		void Clear()
		{
			for (auto head = child_head; head; head = head->next)
			{
				head->Clear();
			}
			if (data)
			{
				delete data;
			}
		}
	};

}

template<typename Char>
class PrefixString
{
	using _Mychar = Char;
	using my_string_view = std::basic_string_view<Char>;
	Internal::PrefixStringTree<Char>& str;
public:
	PrefixString() :str(Internal::PrefixStringTree<Char>::GetRoot()) {};
	PrefixString(my_string_view view) :str(Internal::PrefixStringTree<Char>::GetRoot() + view) {};
	PrefixString(const PrefixString& other) :str(other.str) {};

	my_string_view ReadValue() const
	{
		return str;
	}

	operator my_string_view() const
	{
		return str;
	}
};
	
#endif // !__FILE_Detail_Core_String_H
