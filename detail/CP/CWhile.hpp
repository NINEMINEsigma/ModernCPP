#pragma once
#ifndef __FILE_Detail_CP_CWhile_Hpp
#define __FILE_Detail_CP_CWhile_Hpp

struct CRange
{
	template<template<int> class Callable, size_t End>
	constexpr static void Range()
	{
		Range<Callable, 0, End>();
	}

	template<template<int> class Callable, int Start, int Stop, int Step = 1>
	constexpr static void Range()
	{
		if constexpr (Step == 0)
			static_assert(Step == 0, "Step not support 0");
		Callable<Start> call;
		call();
		if constexpr (Start < Stop && Start + Step > Stop)
			static_assert(Start < Stop && Start + Step > Stop, "While not stop");
		if constexpr (Start > Stop && Start + Step < Stop)
			static_assert(Start > Stop && Start + Step < Stop, "While not stop");
		if constexpr (Start + Step != Stop)
			Range<Callable, Start + Step, Stop, Step>();
	}
};

template<typename... TemplateArgs>
struct CWhile
{
	template<template<typename...> class Callable, template<typename...> class Pr, size_t MaxDepth, typename... Args>
	constexpr static void WhileWithArgs(Args... args)
	{
		Callable<TemplateArgs...> call;
		call(args...);
		Pr<TemplateArgs...> pr;
		if constexpr (pr(args...))
		{
			if constexpr (MaxDepth != 0)
			{
				WhileWithArgs<Callable, Pr, MaxDepth - 1, Args...>(args...);
			}
			else
			{
				static_assert(MaxDepth == 0, "WhileWithArgs is touch MaxDepth");
			}
		}
	}

	template<typename Callable, template<typename...> class Pr, size_t MaxDepth, typename... Args>
	constexpr static void WhileWithArgs(Args... args)
	{
		Callable call;
		call();
		Pr<TemplateArgs...> pr;
		if constexpr (pr(args...))
		{
			if constexpr (MaxDepth != 0)
			{
				WhileWithArgs<Callable, Pr, MaxDepth - 1, Args...>(args...);
			}
			else
			{
				static_assert(MaxDepth == 0, "WhileWithArgs is touch MaxDepth");
			}
		}
	}

	template<template<typename...> class Callable, typename Pr, size_t MaxDepth, typename... Args>
	constexpr static void WhileWithArgs(Args... args)
	{
		Callable<TemplateArgs...> call;
		call(args...);
		Pr pr;
		if constexpr (pr())
		{
			if constexpr (MaxDepth != 0)
			{
				WhileWithArgs<Callable, Pr, MaxDepth - 1, Args...>(args...);
			}
			else
			{
				static_assert(MaxDepth == 0, "WhileWithArgs is touch MaxDepth");
			}
		}
	}

	template<template<int, typename, typename...> class Callable, template<int, typename, typename...> class Pr, size_t MaxDepth, int Start, int Stop, int Step>
	constexpr static void WhileWithTemplate()
	{
		Callable<Start, TemplateArgs...> call;
		call();
		Pr<Start, TemplateArgs...> pr;
		if constexpr (pr())
		{
			if constexpr (MaxDepth != 0)
			{
				if constexpr (Start + Step != Stop)
					WhileWithTemplate<Callable, Pr, MaxDepth - 1, Start + Step, Stop, Step>();
			}
			else
			{
				static_assert(MaxDepth == 0, "WhileWithTemplate is touch MaxDepth");
			}
		}
	}

	template<template<int> class Callable, template<int, typename, typename...> class Pr, size_t MaxDepth, int Start, int Stop, int Step>
	constexpr static void WhileWithTemplate()
	{
		Callable<Start> call;
		call();
		Pr<Start, TemplateArgs...> pr;
		if constexpr (pr())
		{
			if constexpr (MaxDepth != 0)
			{
				if constexpr (Start + Step != Stop)
					WhileWithTemplate<Callable, Pr, MaxDepth - 1, Start + Step, Stop, Step>();
			}
			else
			{
				static_assert(MaxDepth == 0, "WhileWithTemplate is touch MaxDepth");
			}
		}
	}

	template<template<typename...> class Callable, template<int, typename, typename...> class Pr, size_t MaxDepth, int Start, int Stop, int Step>
	constexpr static void WhileWithTemplate()
	{
		Callable<TemplateArgs...> call;
		call();
		Pr<Start, TemplateArgs...> pr;
		if constexpr (pr())
		{
			if constexpr (MaxDepth != 0)
			{
				if constexpr (Start + Step != Stop)
					WhileWithTemplate<Callable, Pr, MaxDepth - 1, Start + Step, Stop, Step>();
			}
			else
			{
				static_assert(MaxDepth == 0, "WhileWithTemplate is touch MaxDepth");
			}
		}
	}

	template<typename Callable, template<int, typename, typename...> class Pr, size_t MaxDepth, int Start, int Stop, int Step>
	constexpr static void WhileWithTemplate()
	{
		Callable call;
		call();
		Pr<Start, TemplateArgs...> pr;
		if constexpr (pr())
		{
			if constexpr (MaxDepth != 0)
			{
				if constexpr (Start + Step != Stop)
					WhileWithTemplate<Callable, Pr, MaxDepth - 1, Start + Step, Stop, Step>();
			}
			else
			{
				static_assert(MaxDepth == 0, "WhileWithTemplate is touch MaxDepth");
			}
		}
	}

	template<template<int, typename, typename...> class Callable, template<int> class Pr, size_t MaxDepth, int Start, int Stop, int Step>
	constexpr static void WhileWithTemplate()
	{
		Callable<Start, TemplateArgs...> call;
		call();
		Pr<Start> pr;
		if constexpr (pr())
		{
			if constexpr (MaxDepth != 0)
			{
				if constexpr (Start + Step != Stop)
					WhileWithTemplate<Callable, Pr, MaxDepth - 1, Start + Step, Stop, Step>();
			}
			else
			{
				static_assert(MaxDepth == 0, "WhileWithTemplate is touch MaxDepth");
			}
		}
	}

	template<template<int, typename, typename...> class Callable, template<typename...> class Pr, size_t MaxDepth, int Start, int Stop, int Step>
	constexpr static void WhileWithTemplate()
	{
		Callable<Start, TemplateArgs...> call;
		call();
		Pr<TemplateArgs...> pr;
		if constexpr (pr())
		{
			if constexpr (MaxDepth != 0)
			{
				if constexpr (Start + Step != Stop)
					WhileWithTemplate<Callable, Pr, MaxDepth - 1, Start + Step, Stop, Step>();
			}
			else
			{
				static_assert(MaxDepth == 0, "WhileWithTemplate is touch MaxDepth");
			}
		}
	}

	template<template<int, typename, typename...> class Callable, typename Pr, size_t MaxDepth, int Start, int Stop, int Step>
	constexpr static void WhileWithTemplate()
	{
		Callable<Start, TemplateArgs...> call;
		call();
		Pr pr;
		if constexpr (pr())
		{
			if constexpr (MaxDepth != 0)
			{
				if constexpr (Start + Step != Stop)
					WhileWithTemplate<Callable, Pr, MaxDepth - 1, Start + Step, Stop, Step>();
			}
			else
			{
				static_assert(MaxDepth == 0, "WhileWithTemplate is touch MaxDepth");
			}
		}
	}

	template<template<int> class Callable, template<int> class Pr, size_t MaxDepth, int Start, int Stop, int Step>
	constexpr static void WhileWithTemplate()
	{
		Callable<Start> call;
		call();
		Pr<Start> pr;
		if constexpr (pr())
		{
			if constexpr (MaxDepth != 0)
			{
				if constexpr (Start + Step != Stop)
					WhileWithTemplate<Callable, Pr, MaxDepth - 1, Start + Step, Stop, Step>();
			}
			else
			{
				static_assert(MaxDepth == 0, "WhileWithTemplate is touch MaxDepth");
			}
		}
	}

	template<template<int> class Callable, template<typename...> class Pr, size_t MaxDepth, int Start, int Stop, int Step>
	constexpr static void WhileWithTemplate()
	{
		Callable<Start> call;
		call();
		Pr<TemplateArgs...> pr;
		if constexpr (pr())
		{
			if constexpr (MaxDepth != 0)
			{
				if constexpr (Start + Step != Stop)
					WhileWithTemplate<Callable, Pr, MaxDepth - 1, Start + Step, Stop, Step>();
			}
			else
			{
				static_assert(MaxDepth == 0, "WhileWithTemplate is touch MaxDepth");
			}
		}
	}

	template<template<int> class Callable, typename Pr, size_t MaxDepth, int Start, int Stop, int Step>
	constexpr static void WhileWithTemplate()
	{
		Callable<Start> call;
		call();
		Pr pr;
		if constexpr (pr())
		{
			if constexpr (MaxDepth != 0)
			{
				if constexpr (Start + Step != Stop)
					WhileWithTemplate<Callable, Pr, MaxDepth - 1, Start + Step, Stop, Step>();
			}
			else
			{
				static_assert(MaxDepth == 0, "WhileWithTemplate is touch MaxDepth");
			}
		}
	}

	template<template<typename...> class Callable, template<int> class Pr, size_t MaxDepth, int Start, int Stop, int Step>
	constexpr static void WhileWithTemplate()
	{
		Callable<TemplateArgs...> call;
		call();
		Pr<Start> pr;
		if constexpr (pr())
		{
			if constexpr (MaxDepth != 0)
			{
				if constexpr (Start + Step != Stop)
					WhileWithTemplate<Callable, Pr, MaxDepth - 1, Start + Step, Stop, Step>();
			}
			else
			{
				static_assert(MaxDepth == 0, "WhileWithTemplate is touch MaxDepth");
			}
		}
	}

	template<template<typename...> class Callable, typename Pr, size_t MaxDepth, int Start, int Stop, int Step>
	constexpr static void WhileWithTemplate()
	{
		Callable<TemplateArgs...> call;
		call();
		Pr pr;
		if constexpr (pr())
		{
			if constexpr (MaxDepth != 0)
			{
				if constexpr (Start + Step != Stop)
					WhileWithTemplate<Callable, Pr, MaxDepth - 1, Start + Step, Stop, Step>();
			}
			else
			{
				static_assert(MaxDepth == 0, "WhileWithTemplate is touch MaxDepth");
			}
		}
	}
};

#endif // !__FILE_Detail_CP_CWhile_Hpp
