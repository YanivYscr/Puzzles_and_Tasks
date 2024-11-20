        #include <map>
        #include <string>
        #include <limits>
        #include <iostream>
        #include <iostream> 

        using namespace std;

        template<typename K, typename V>
        class interval_map {
        public:
            interval_map(V const& val)
                : m_valBegin(val)
            {}

            void Print()
            {
                int min_int = std::numeric_limits<int>::min();
                std::cout << (*this)[min_int] << " : " << " -inf" << std::endl;
                for (const auto& it : m_map)
                    std::cout << it.second << " : " << it.first << std::endl;
                std::cout << std::endl;
            }
            // TASK:
            // Assign value val to interval [keyBegin, keyEnd).
            // Overwrite previous values in this interval.
            // Conforming to the C++ Standard Library conventions, the interval
            // includes keyBegin, but excludes keyEnd.
            // If !( keyBegin < keyEnd ), this designates an empty interval,
            // and assign must do nothing.

            void assign(K const& keyBegin, K const& keyEnd, V const& val)
            {
                
                if(CheckKeyValidation(keyBegin,keyEnd,val) == false)
                    return;
                    
                const V v_begin = (*this)[keyBegin];
                const V v_end = (*this)[keyEnd];

                if (val != v_begin)
                    m_map[keyBegin] = val;
                if (val != v_end)
                    m_map[keyEnd] = v_end;    
            
                auto start = m_map.upper_bound(keyBegin);
                auto end   = m_map.lower_bound(keyEnd);

                if (start != m_map.end() && start != end)
                    m_map.erase(start, end);

                auto prev_iter = m_map.find(keyBegin);

                if (prev_iter != m_map.end())
                {
                    V prev_value = (*this)[keyBegin];

                    if (prev_iter != m_map.begin())
                        prev_value = (--prev_iter)->second;
                    else
                        prev_value = m_valBegin;
                    if (val == prev_value)
                        m_map.erase(keyBegin);
                }

                if (end != m_map.end() && (*this)[keyBegin] == (*this)[keyEnd])
                    m_map.erase(end);
            }

            // look-up of the value associated with key
            V const& operator[](K const& key) const {
                auto it = m_map.upper_bound(key);
                if (it == m_map.begin()) {
                    return m_valBegin;
                }
                else {
                    return (--it)->second;
                }
            }
        private:
            friend void IntervalMapTest();
            V m_valBegin;
            std::map<K, V> m_map;

            bool CheckKeyValidation(K const& keyBegin, K const& keyEnd, V const& val)
            {
                auto it1 = m_map.find(keyBegin);
                auto it2 = m_map.find(keyEnd);    

                if(it1 == m_map.end())
                    m_map[keyBegin] = val;
                if(it2 == m_map.end())
                    m_map[keyEnd] = val;
                    
                bool is_valid_distance = std::distance(m_map.begin(), m_map.find(keyBegin)) < std::distance(m_map.begin(), m_map.find(keyEnd));

                if(it1 == m_map.end())    
                    m_map.erase(keyBegin);
                if(it2 == m_map.end())
                    m_map.erase(keyEnd);

                return is_valid_distance;
            }
        };

        void test_01()
        {
            interval_map<int, std::string> map_01("A");
            map_01.assign(10, 22, "TR");
            map_01.Print();
            map_01.assign(10, 22, "A");
            map_01.Print();

            // Assign some values
            map_01.assign(111111, 3111, "B");
            map_01.assign(-10, 311, "C");
            map_01.assign(5, 17, "D");
            map_01.assign(10, 22, "A");
            map_01.assign(5, 71, "D");

            map_01.Print();
            std::cout << std::endl;
        }

        void test_02()
        {
            interval_map<int, std::string> map_02("A");
            map_02.assign(111111, 3111, "B");
            map_02.assign(-10, 311, "C");
            map_02.assign(5, 17, "D");
            map_02.assign(10, 22, "A");
            map_02.assign(5, 71, "D");
            map_02.Print();

            map_02.assign(5, 71, "D");
            map_02.assign(5, 17, "D");
            map_02.assign(10, 22, "A");
            map_02.assign(-10, 311, "C");
            map_02.assign(1, 3111, "B");

            map_02.Print();
        }

        void test_03()
        {
            interval_map<int, std::string> map_03("A");

            map_03.assign(5, 20, "B");
            map_03.Print();

            map_03.assign(-1, 7, "C");
            map_03.Print();

            map_03.assign(-1, 7, "A");
            map_03.Print();

            map_03.assign(5, 19, "D");
            map_03.Print();

            map_03.assign(5, 19, "A");
            map_03.Print();
            map_03.assign(5, 20, "A");
            map_03.assign(5, 24, "A");
            map_03.assign(5, 24, "c");
            map_03.assign(5, 23, "A");
            map_03.Print();
            map_03.assign(24, 25, "F");
            map_03.Print();
            map_03.assign(25, 26, "F");
            map_03.assign(215, 26, "ZZ");
            map_03.assign(28, 29, "H");
            map_03.Print();
            map_03.assign(-8, 239, "A");
            map_03.Print();

            //map_03.assign(5, 211, "A");
            //map_03.assign(5, 71, "D");
            //map_03.Print();
            //map_03.assign(5, 71, "D");
            //map_03.assign(5, 17, "D");
            //map_03.assign(10, 22, "A");
            //map_03.assign(-10, 311, "C");
            //map_03.assign(1, 3111, "B");

        }

        
        int main() {
            //Visual Tests
            test_01();
            test_02();
            test_03();
            return 0;
        }