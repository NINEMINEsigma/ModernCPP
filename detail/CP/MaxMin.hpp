#pragma once
#ifndef __FILE_Detail_CP_MaxMin_Hpp
#define __FILE_Detail_CP_MaxMin_Hpp

namespace Internal
{
    template<typename A, typename B> struct MaxMinFoucsValueConditionalTool
    {
        constexpr static bool ABS = (!!sizeof(A) > sizeof(B));
        using AF = std::conditional_t<std::is_floating_point_v<B>,
            std::conditional_t < ABS, A, B>,
            A
        >;
        using BF = std::conditional_t<std::is_floating_point_v<B>,
            B,
            std::conditional_t < ABS, A, B>
        >;
        using Type = std::conditional_t < std::is_floating_point_v<A>, AF, BF>;
    };
}

template<typename A, typename B> using MaxMinFoucsValueConditional = typename Internal::MaxMinFoucsValueConditionalTool<A, B>::Type;

template<typename First, typename Second> auto Max(const First& first, const Second& second)
{
    return std::max<MaxMinFoucsValueConditional<First, Second>>(first, second);
}
template<typename First, typename Second, typename... Args> auto Max(const First& first, const Second& second, const Args&... args)
{
    return Max(std::max<MaxMinFoucsValueConditional<First, Second>>(first, second), args...);
};
template<typename First, typename Second> auto Min(const First& first, const Second& second)
{
    return std::min<MaxMinFoucsValueConditional<First, Second>>(first, second);
}
template<typename First, typename Second, typename... Args> auto MIn(const First& first, const Second& second, const Args&... args)
{
    return Min(std::min<MaxMinFoucsValueConditional<First, Second>>(first, second), args...);
};

#endif // !__FILE_Detail_CP_MaxMin_Hpp

