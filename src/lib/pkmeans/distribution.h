#ifndef __DISTRIBUTION_H_INCLUDED_
#define __DISTRIBUTION_H_INCLUDED_

#include <vector>
#include <sstream>
#include <algorithm>
#include <tgmath.h>

namespace pkmeans {
template <class T>
struct Distribution {
    private:
        std::vector<T> buckets;
    public:
        Distribution () {};

        size_t size () const {
            return buckets.size ();
        };

        void fill (T value) {
            std::fill (buckets.begin (), buckets.end (), value);
        };

        T sum () const {
            T retSum = 0;
            for (size_t i = 0; i < size (); i++) {
                retSum += buckets[i];
            }
            return retSum;
        }

        T absSum () const {
            T retSum = 0;
            for (size_t i = 0; i < size (); i++) {
                retSum += fabs (buckets[i]);
            }
            return retSum;
        }

        T& operator[] (size_t idx) {
            return buckets[idx];
        };

        const T& operator[] (size_t idx) const {
            return buckets[idx];
        };

        Distribution& operator= (const Distribution &other) {
            if (this != &other) {
                buckets = other.buckets;
            }
            return *this;
        }

        Distribution& operator+= (const Distribution &other) {
            for (size_t i = 0; i < size (); i++) {
                buckets[i] += other.buckets[i];
            }
            return *this;
        }

        Distribution& operator-= (const Distribution &other) {
            for (size_t i = 0; i < size (); i++) {
                buckets[i] -= other.buckets[i];
            }
            return *this;
        };

        Distribution& operator*= (const Distribution &other) {
            for (size_t i = 0; i < size (); i++) {
                buckets[i] *= other.buckets[i];
            }
            return *this;
        };

        Distribution& operator*= (const T &rhs) {
            for (size_t i = 0; i < size (); i++) {
                buckets[i] *= rhs;
            }
            return *this;
        };

        Distribution& operator/= (const Distribution &other) {
            for (size_t i = 0; i < size (); i++) {
                buckets[i] /= other.buckets[i];
            }
            return *this;
        };

        Distribution& operator/= (const T &rhs) {
            for (size_t i = 0; i < size (); i++) {
                buckets[i] /= rhs;
            }
            return *this;
        };

        friend bool operator== (const Distribution &lhs, const Distribution &rhs) {
            if (lhs.size () != rhs.size ())
                return false;
            for (size_t i = 0; i < lhs.size (); i++) {
                if (lhs[i] != rhs[i])
                    return false;
            }
            return true;
        }

        friend bool operator!= (const Distribution &lhs, const Distribution &rhs) {
            return !(lhs == rhs);
        }

        friend std::istream& operator>> (std::istream &is, Distribution &obj) {
            T tempVal;
            std::string buf;
            std::getline (is, buf);
            std::istringstream iss (buf);
            while (iss) {
                if (!(iss >> tempVal))
                    break;
                obj.buckets.push_back (tempVal);
            }
            return is;
        };

        friend std::ostream& operator<< (std::ostream &os, const Distribution &obj) {
            for (size_t i = 0; i < obj.buckets.size () - 1; i++) {
                os << obj.buckets[i] << ' ';
            }
            os << obj.buckets[obj.buckets.size () - 1];
            return os;
        };

        friend Distribution operator+ (Distribution lhs, const Distribution &rhs) {
            lhs += rhs;
            return lhs;
        };

        friend Distribution operator- (Distribution lhs, const Distribution &rhs) {
            lhs -= rhs;
            return lhs;
        };

        friend Distribution operator* (Distribution lhs, const Distribution &rhs) {
            lhs *= rhs;
            return lhs;
        };

        friend Distribution operator* (Distribution lhs, const T &rhs) {
            for (size_t i = 0; i < lhs.size (); i++) {
                lhs.buckets[i] *= rhs;
            }
            return lhs;
        };

        friend Distribution operator* (const T &lhs, Distribution rhs) {
            for (size_t i = 0; i < rhs.size (); i++) {
                rhs.buckets[i] *= lhs;
            }
            return rhs;
        };

        friend Distribution operator/ (Distribution lhs, const Distribution &rhs) {
            lhs /= rhs;
            return lhs;
        };

        friend Distribution operator/ (Distribution lhs, const T &rhs) {
            for (size_t i = 0; i < lhs.size (); i++) {
                lhs.buckets[i] /= rhs;
            }
            return lhs;
        };

        friend Distribution operator/ (const T &lhs, Distribution rhs) {
            for (size_t i = 0; i < rhs.size (); i++) {
                rhs.buckets[i] /= lhs;
            }
            return rhs;
        };

        static double emd (const Distribution &d1, const Distribution &d2) {
            Distribution emdDistribution = d1 - d2;
            for (size_t i = 1; i < emdDistribution.size (); i++) {
                emdDistribution[i] += emdDistribution[i - 1];
            }
            return emdDistribution.absSum ();
        };
};
}

#endif // __DISTRIBUTION_H_INCLUDED_
