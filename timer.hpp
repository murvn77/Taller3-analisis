#include <chrono>
#include <utility>
namespace timer {
template <typename _Funtion, typename... _Args>
std::chrono::duration<double> measureTime(_Funtion f, _Args &&..._args) {
    auto start = std::chrono::steady_clock::now();
    f(_args...);
    auto end = std::chrono::steady_clock::now();
    return end - start;
}

template <typename _Function, typename... _Args,
          typename _ReturnType =
              decltype(std::declval<_Function>()(std::declval<_Args>()...))>
std::pair<std::chrono::duration<double>, _ReturnType>
measureTimeR(_Function f, _Args &&..._args) {
    auto start = std::chrono::steady_clock::now();
    _ReturnType r = f(_args...);
    auto end = std::chrono::steady_clock::now();
    return {end - start, r};
}

template<typename _TreeType,typename _T, typename _Units = std::chrono::nanoseconds>
double measure(_TreeType tree, _T elem, int times){
    std::chrono::duration<double> m {0};
    auto lambda = [&](){
        tree.search(elem);
    };
    for(int i = 0; i< times; i++){
        m += timer::measureTime(lambda);
    }
    return std::chrono::duration_cast<_Units>(m/times).count();
}

} // namespace timer
