# Class UMap
### Educational project!!!
### Template class represent a simplified realization of a hash table.

# Template parameters:
- `Key` - type of key.
- `Value` - type of value.




# Public methods:
- `UMap()` - default constructor.
- `UMap(const UMap& other)` - copy constructor.
- `UMap(UMap&& other)` - move constructor.
- `~UMap()` - virtual destructor.
- `UMap& operator=(const UMap& other)` - copy assignment operator.
- `void add(const Key& key, const Value& value)`-add new element to the map.
- `std::optional<Value> getValue(const Key& key)` - get value by key.
- `bool remove(const Key& key)` - remove element by key.
- `bool contains(const Key& key)` - check if the map contains the key.
- `std::optional<std::pair<Key,Value>&> getPair(const Key& key)` - get pair by key.
- `void clear()` - clear the map.
- `size_t size()` - get the size of the map.
- `size_t capacity()` - get the capacity of the map.
- `Value& operator[](const Key& key)` - get value by key.

# Iterator:
- `class Iterator` - iterator for the map, support range-based for loop.
- `Iterator begin()` - get iterator to the first element.
- `Iterator end()` - get iterator to the last element.


# Private methods:
- `void resize()` - rehash the map.

# Benchmark:
![Banchmark](https://github.com/user-attachments/assets/e3f3c089-1f93-4ea9-972b-c649fd8fffd1)

    





