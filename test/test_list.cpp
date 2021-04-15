#include "list.h"
#include <gtest.h>

TEST(LinkPointer, can_create)
{
	ASSERT_NO_THROW(List<int>::LinkPointer ind);
}

TEST(LinkPointer, can_create_copied)
{
	List<int>::LinkPointer i1;
	List<int>::LinkPointer i2(i1);
	ASSERT_NO_THROW(i2);
}

TEST(List, can_add_node_in_end)
{
	List<int> list;
	ASSERT_NO_THROW(list.PushBack(5));
}

TEST(List, can_compare_two_same_lists)
{
	List<int> list1;
	List<int> list2;
	list1.PushBack(5);
	list2.PushBack(5);
	EXPECT_TRUE(list1 == list2);
}

TEST(List, can_compare_two_different_lists)
{
	List<int> list1;
	List<int> list2;

	list1.PushBack(5);
	list2.PushBack(55);
	EXPECT_TRUE(list1 != list2);
}

TEST(List, can_check_for_empty)
{
	List<int> list;
	EXPECT_TRUE(list.IsEmpty());
}

TEST(List, two_lists_with_different_sizes_are_not_equal)
{
	List<int> list1;
	List<int> list2;
	for (int i = 1; i < 5; i++)
	{
		list1.PushBack(i);
	}
	list2.PushBack(5);
	EXPECT_TRUE(list1 != list2);
}

TEST(List, can_delete_node)
{
	List<int> list;
	List<int>::LinkPointer i;
	list.PushBack(5);
	i = list.Begin();
	ASSERT_NO_THROW(list.RemoveAt(i));
}

TEST(List, can_insert_node)
{
	List<int> list;
	List<int>::LinkPointer i;
	i = list.Begin();
	list.Insert(i, 3);
	EXPECT_TRUE(1 == list.GetSize());
}

TEST(List, can_return_size_of_list)
{
	List<int> list;
	for (int i = 0; i < 5; i++)
	{
		list.PushBack(i);
	}
	EXPECT_TRUE(5 == list.GetSize());
}

TEST(TList, can_add_node_in_end)
{
	List<int> list;
	ASSERT_NO_THROW(list.PushBack(5));
}

TEST(List, method_del_delete_all_nodes_of_list)
{
	List<int> list;
	for (int i = 0; i < 5; i++)
	{
		list.PushBack(i);
	}
	list.DeleteAllNodes();
	EXPECT_TRUE(list.IsEmpty());
}