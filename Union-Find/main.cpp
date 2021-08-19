/* This is an implementation of union find, a very basic implementation using std::map in C++
 * TODOs:
 *      * Use DEBUG macro, to print statements useful for debugging.
 *      * Using comparator vs < operator overload? Which one is better for std::map for user-defined types?
 *      * Use const reference wherever possible.
 *      * Add testing.
 *      * Graph should be a class template.
 * @author: krshrimali (github.com/krshrimali)
 * Date: 19/08/2021
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

/* This is a sample class in order to use std::map
 * As per name, it will have (x, y) coordinates, take it like a point in a map
 */
struct Point {
    int x;
    int y;
    
    Point(int inp_x, int inp_y): x(inp_x), y(inp_y) {}

    // TODO: Instead use a Copy Constructor
    Point operator=(Point obj_a) {
        return Point(obj_a);
    }

    // Since we use std::find and it uses comparison operator, it's necessary to have an overload here
    // https://stackoverflow.com/a/1102720 (TODO, have a comparator class instead?)
    bool operator<(const Point& rhs) const {
        // NOTE: using return (rhs.x < this->x) || (rhs.y < this->y)l didn't work 
        if ((rhs.x < this->x) || (rhs.y < this->y)) return true;
        else return false;
    }

    // Used by map.find() function
    bool operator==(const Point& rhs) const {
        return (this->x == rhs.x) && (this->y == rhs.y);
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << '(' << p.x << ", " << p.y << ')';
        return os;
    }
};

// You can also use a comparator struct instead of overloading < for Point struct
// This is optional, and hence commented out but good for learning
/* struct PointComparator {
    bool operator()(const Point& left, const Point& right) const {
        if ((left.x < right.x) || (left.y < right.y)) return true;
        else return false;
    }
};*/

class Graph {
private:
    // Uncomment below line in case you want to use PointComparator
    // std::map<Point, std::vector<Point>, PointComparator > graph;
    std::map<Point, std::vector<Point> > graph;
    const std::vector<Point> get_connected_points(Point a) {
        return this->graph.at(a);
    }
public:
    friend std::ostream& operator<<(std::ostream& os, const Graph& g) {
        for (auto const& x: g.graph) {
            // os << x.first << ", " << x.second << std::endl;
            os << "Key: " << x.first << std::endl;
            os << "Connected to: ";
            for (auto point: x.second) {
                os << point << " ";
            }
        }
        return os;
    }

    /* Connect a and b points in the graph */
    void union_(const Point& a, const Point& b) {

        // a not found in the graph
        if (this->graph.find(a) == this->graph.end()) {
            std::cout << " not found: " << a << std::endl;
            this->graph[a] = {b};
        } else {
            // TODO: This doesn't take care of duplicates
            // Note: insert takes care of duplicates in std::map
            this->graph.at(a).push_back(b);
        }
    }

    /* Are a and b connected? OR Is there a path b/w a and b? */
    bool find_(const Point& a, const Point& b) {

        if (this->graph.find(a) == this->graph.end()) {
            // TODO: Should this be std::cerr?
            // Add an assertion instead?
            std::cout << "First object not found in the graph\n";
            return false;
        } else {
            /* Object found, let's search for point b in the graph now */
            auto connected_points = get_connected_points(a); 
            /* for (auto point: connected_points) {
                std::cout << point.x << ", " << point.y << std::endl;
            } */
            if (std::find(connected_points.begin(), connected_points.end(), b) != connected_points.end()) {
                // b found!
                return true;
            }
            return false;
        }
    }

    void print_graph() {
        if (this->graph.size() == 0) std::cout << "Graph is empty, hmm! Care to fill it yet? ;)\n";
        else {
            // This works because we have overloaded operator <<
            std::cout << *this;
            std::cout << std::endl;
        }
    }

};

int main() {
    Graph sampleGraph;
    struct Point p(2, 3);
    struct Point q(3, 3);
    struct Point r(4, 4);

    sampleGraph.union_(p, q);
    sampleGraph.union_(p, r);

    std::cout << "Are p and q connected? Answer: " << sampleGraph.find_(p, q) << '\n';  // Expected: true
    std::cout << "Are p and r connected? Answer: " << sampleGraph.find_(p, r) << '\n';  // Expected; true
    std::cout << "Are q and r connected? Answer: " << sampleGraph.find_(q, r) << '\n';  // Expected: false

    sampleGraph.print_graph();
}
