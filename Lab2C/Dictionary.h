#pragma once
#include "Sequence.h"

typedef ArraySequence<char> String;
// record structure
typedef struct Record {
	String word;
	ArraySequence<int> entries;
	int count;
} Record;
typedef LinkedListSequence<String> StringList;
typedef LinkedListSequence<Record> RecordList;

template<typename T>
class Dictionary
{
	bool Equal(const String _string1, const String _string2) {
		if (&_string1 == &_string2)
			return true;
		if (_string1.GetLength() == _string2.GetLength())
		{
			for (size_t i = 0; i < _string1.GetLength(); i++)
				if (_string1.Get(i) != _string2.Get(i)) {
					return false;
				}
			return true;
		}
		return false;
	}

public:
	// constructors --------------------------------------------------------
	Dictionary() {
		this->list = new RecordList;
		this->banlist = new StringList;
	}

	/*
	Dictionary(const LinkedList<String>& _list, const LinkedList<String>& _banlist) {
		this->list = new RecordList(_list);
		this->banlist = new StringList(_banlist);
	}
	*/

	// string to splitted sequence
	Dictionary(const String& _string) {
		this->list = new RecordList;
		this->banlist = new StringList;
		this->AddString(_string);
	}

	// functions -----------------------------------------------------------
	void Add(String item, int index) {
		for (int i = 0; i < list->GetLength(); i++) {
			Record record = list->Get(i);
			String word = record.word;
			if (Equal(word, item)) {
				record.count++;
				record.entries.Append(index);
				list->Set(record, i);
				return;
			}
		}
		for (int i = 0; i < banlist->GetLength(); i++) {
			if (Equal(banlist->Get(i), item)) {
				return;
			}
		}
		Record record;
		record.word = item;
		record.count = 1;
		record.entries.Append(index);
		list->Append(record);
		int x = 0;
	}

	void AddString(const String& _string) {
		int length = _string.GetLength();
		String word;
		char elem, c;
		int temp, end;
		int start = 0;
		for (int i = 0; i < length; i++) {
			elem = _string[i];
			temp = static_cast<int>(elem);
			if (i == length - 1 || elem == ' ') {
				end = i - 1;
				if (i == length - 1) end++;
				//check end
				for (int j = end; j >= start; j--) {
					temp = static_cast<int>(_string[j]);
					// check if not symb
					if ((temp > -1 & temp < 65) || (temp > 90 & temp < 97) || (temp > 122)) {
						end--;
					}
					else break;
				}
				//check start
				for (int j = start; j <= end; j++) {
					temp = static_cast<int>(_string[j]);
					// check if not symb
					if ((temp > -1 & temp < 65) || (temp > 90 & temp < 97) || (temp > 122)) {
						start++;
					}
					else break;
				}

				// load into word
				String word(end - start + 1);
				for (int j = 0; j <= end - start; j++) {
					c = _string[j + start];
					word.Set(c, j);
				}
				// append to splitted
				this->Add(word, start);
				start = i + 1;
			}
		}
	}

	void AddBanned(String item) {
		banlist->Append(item);
		for (int i = 0; i < list->GetLength(); i++) {
			if (Equal(list->Get(i).word, item)) {
				list->RemoveAt(i);
				return;
			}
		}
	}

	StringList* GetList() {
		return this->list;
	}

	size_t GetLength() {
		return this->list->GetLength();
	}

	Record GetRecord(const size_t index) {
		return (*(this->list))[index];
	}

	String GetWord(const size_t index) {
		return (*(this->list))[index].word;
	}

	int GetWordCount(const size_t index) {
		return (*(this->list))[index].count;
	}

	ArraySequence<int> GetWordEntries(const size_t index) {
		return (*(this->list))[index].entries;
	}

	// operators -----------------------------------------------------------
	T operator[](const size_t index) {
		return this->GetWord(index);
	}

	const T operator[](const size_t index) const {
		return this->Get(index);
	}

	~Dictionary() { 
		delete[] this->list;
		delete[] this->banlist;
	}
private:
	RecordList* list;
	StringList* banlist;
};