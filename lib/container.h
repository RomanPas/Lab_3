#include <memory>

struct Node
{
	int value;
	Node* next;
	Node* prev;
};

template<typename T, typename Allocator = std::allocator<T>>
class Container
{
	using CAllocator = typename Allocator::template rebind<Node>::other;
public:
	Container() {
		head_ = nullptr;
		tail_ = nullptr;
	};
	~Container() {
		if (head_)
			clear();
		head_ = nullptr;
		tail_ = nullptr;
	}
	void push_back(const T& value) {
		auto newNode = my_alloc.allocate(1);
		my_alloc.construct(newNode);
		newNode->value = value;
		newNode->next = nullptr;
		if (head_ == nullptr) {
			newNode->prev = nullptr;
			head_ = newNode;
			tail_ = head_;
		}
		else {
			newNode->prev = tail_;
			newNode->value = value;
			tail_->next = newNode;
			tail_ = tail_->next;
		}
	}
	void print() {
		Node* node = head_;
		while (node != nullptr) {
			std::cout << node->value << std::endl;
			node = node->next;
		}
	}
private:
	CAllocator my_alloc;
	Node* head_;
	Node* tail_;

	void clear() {
		Node* next;
		while (tail_ != nullptr) {
			next = tail_->prev;
			my_alloc.destroy(tail_);
			my_alloc.deallocate(tail_, 1);
			tail_ = next;
		}
	}
};