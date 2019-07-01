#include <iostream>
#include <string>
#include <memory>
#include <cassert>

#include "counter.hpp"

#define compound(item) stringify(item.err)
#define DefineErrorFilename(item) #item

#define ListName_ Code
#define ErrorFile_ "LoadFileDataResult.err"
#define ClassName_ LoadFileDataResultClass
#include "class"


DefineCompileTimeCounter(GlobalCounter1);

enum class ValuesAA
{
	A = GlobalCounter1Next(),
	B,
	C,
	D,
	Max
};

enum class ValuesBB
{
	A = GlobalCounter1Next(),
	B,
	C,
	D,
	Max
};

template<typename EnumType>
uint64_t EnumToUint64(const EnumType& value)
{
	return static_cast<uint64_t>(value);
}

DefineCompileTimeCounter(Jon);
DefineCompileTimeCounter(Another); 

void Roller()
{
	std::cout << EnumToUint64(ValuesAA::A) << std::endl;
	std::cout << EnumToUint64(ValuesAA::B) << std::endl;
	std::cout << EnumToUint64(ValuesAA::C) << std::endl;
	std::cout << EnumToUint64(ValuesAA::D) << std::endl;
	std::cout << "----" << std::endl;

	std::cout << EnumToUint64(ValuesBB::A) << std::endl;
	std::cout << EnumToUint64(ValuesBB::B) << std::endl;
	std::cout << EnumToUint64(ValuesBB::C) << std::endl;
	std::cout << EnumToUint64(ValuesBB::D) << std::endl;
	std::cout << "----" << std::endl;

	auto one = JonNext();
	auto two = JonNext();
	auto three = JonNext();

	auto anotherOne = AnotherNext();
	auto anotherTwo = AnotherNext();
	auto anotherThree = AnotherNext();

	std::cout << one << " " << two << " " << three << std::endl;
	std::cout << anotherOne << " " << anotherTwo << " " << anotherThree << std::endl;
	
	constexpr int a = GlobalCounter1Next();
	constexpr int b = GlobalCounter1Next();
	constexpr int c = GlobalCounter1Next();

	std::cout << a << " " << b << " " << c << std::endl;
}

#include "ErrorHeader.h"
#define ErrorFile_ "LoadFileDataResult.err"
//GenList(Results)

class Bar : public std::enable_shared_from_this<Bar>
{
public:
	const int index{ JonNext() };

	void Print() { std::cout << "Bar [" << index << "]" << std::endl; }

	std::shared_ptr<Bar> GetShared()
	{
	return shared_from_this();
	}

	std::weak_ptr<Bar> GetWeak()
	{
		return weak_from_this();
	}

};

#include <vector>


#include <string>

#include <map>
#include <thread>
#include <functional>

#include "State.h"
#include "Event.h"
#include "ActionResult.h"
#include "StateMachine.h"
#include "EventSystem.h"

using namespace xelous;

class StartEvent : public Event
{
public:
	static constexpr EventId Id{ 1 };

	StartEvent()
		:
		Event(Id)
	{
	}
};

class StopEvent : public Event
{
public:
	static constexpr EventId Id{ 2 };

	StopEvent()
		:
		Event(Id)
	{
	}
};

class PayLoadEvent : public Event
{
public:
	static constexpr EventId Id{ 3 };

	PayLoadEvent()
		:
		Event(Id)
	{
	}

	inline const std::string& GetMessage() const { return mMessage; }

	void SetMessage(const std::string& pMessage)
	{
		mMessage = pMessage;
	}

	void operator++()
	{
		++counter;
	}

	inline const int& GetCounter() const { return counter; }

private:
	std::string mMessage{ "" };
	int counter{ 0 };
};


class AState : public State
{
public:
	AState() :
		State("AState")
	{
		AddEventHandlerHelper(af1, StartEvent::Id, &AState::OnAnother);
		AddEventHandlerHelper(af2, StopEvent::Id, &AState::OnStop);
		AddEventHandlerHelper(af3, PayLoadEvent::Id, &AState::OnPayload);
	}
	
    ActionFunctionHelper(OnAnother)
	{
		actionResultOut.first = ActionResultCode::ExitState;
		std::cout << "AState::OnAnother" << std::endl;
		return true;
	}
	
    ActionFunctionHelper(OnStop)
	{
		actionResultOut.first = ActionResultCode::ExitStateMachine;
		return true;
	}
	
    ActionFunctionHelper(OnPayload)
	{
		if (theEventIn != nullptr)
		{
			MakeEventLocalAs(theEventIn, PayLoadEvent, pe);

			if (pe->GetCounter() == 0)
			{
				pe->SetMessage("We just set the message");
			}
			else if (pe->GetCounter() == 1)
			{
				pe->SetMessage("We just changed that message");
			}
			else
			{
				std::cout << std::to_string(pe->GetCounter()) << std::endl;
			}
			++(*pe);
		}
		return true;
	}
};

const bool HelloWorld(Event* const e, [[maybe_unused]] ActionResult& ar)
{
	std::cout << "Event Came in: " << e->Id << std::endl;

	ar.first = ActionResultCode::NewState;
	ar.second = new AState();

	
	return true;
}


class SomethingElse
{
public:
	int* block;
	int shared{ 0 };

	SomethingElse()
		:
		block(new int[8192000])
	{
	}

	~SomethingElse()
	{
		delete[] block;
	}
};

#include <ctime>
#include <iomanip>
#include <locale>
#include <iosfwd>
#include <sstream>

const bool ParseDateString(
    const std::string& dateString,
    std::tm& theTime,
    const std::string& format = "%m/%d/%Y")    
{
    // NOTE: this function assumed you want to consume ALL the input string
    // as a full date, so you must trim white space before passing it in here

    bool parseResult{ false };

    if (!dateString.empty() && !format.empty() )
    {
        std::istringstream inputStream(dateString);        
       
        auto locale = std::locale("en_US.utf8");
        auto& facet = std::use_facet<std::time_get<char>>(locale);
        constexpr std::istreambuf_iterator<char> last{};
        std::ios_base::iostate streamErrorBit = std::ios_base::goodbit;

        auto result = facet.get(
            { inputStream },                    // Copy of the input stream
            {},                                 // End iterator for the input stream
            inputStream,                        // The source stream is also our output stream (self consuming) (const N Time)
            streamErrorBit,                     // A bit into which we set an error
            &theTime,                           // The output tm structure
            &format[0],                         // Pointer to format start
            &format[0] + format.size());        // Format limit
        if (inputStream)
        {
            // Parse good
            parseResult = true;

            if (result == last)
            {
                // TODO - we used everything in the input stream
                // this is good
            }
            else
            {
                // TODO - we didn't use everything, this maybe considered
                // an error if we intended to use everything (see first line comment)
            }
        }
        else
        {
            // TODO - Report failed to parse
        }
    }
    else
    {
        // TODO - Report invalid parameter
    }
        
    return parseResult;
}

int main()
{	
    std::tm t = {};
    t.tm_mday = 20;
    t.tm_year = 71;
    t.tm_mon = 8;

    std::ostringstream os;
    os.imbue(std::locale("en_US.utf8"));
    os << std::put_time(&t, "%x");    

    std::tm s = {};    

    //std::istringstream ss(os.str());
    //ss.imbue(std::locale("en_US.utf8"));
    //ss >> std::get_time(&s, "%x");
    if (ParseDateString(os.str(), s))
    {
        std::cout << "Parse Sucess";


        if (s.tm_mon == t.tm_mon &&
            s.tm_mday == t.tm_mday &&
            s.tm_year == t.tm_year )
        {
            // Note, s == t doesn't work directly, you need a global namespace operator==

            std::cout << "DO THE KESTREL REQUIRE IF YOU LIKE" << std::endl;
        }
    }
    else
    {
        std::cout << "Failed";
    }
    std::cout << std::endl;
    
    
    
    
    /*auto locale = std::locale("en_US.utf8");
    auto& facet = std::use_facet<std::time_get<char>>(locale);
    std::tm theTimeBack{};
    std::string dateFormat = "%m/%d/%Y";
    std::ios_base::iostate streamErrorBit = std::ios_base::goodbit;
    ss.setstate(streamErrorBit);

    auto result = facet.get({ ss }, {}, ss, streamErrorBit, &theTimeBack, &dateFormat[0], &dateFormat[0] + dateFormat.size());
    
    std::istreambuf_iterator<char> last{};
    if (ss) 
    {
        std::cout << "Successfully parsed as " << std::put_time(&theTimeBack, "%x");
        if (result == last) 
        {
            std::cout << " The input was fully consumed";
        }
    }
    else 
    {
        std::cout << "Parse failed. Unparsed string: ";        
    }*/


    //REQUIRE(s == t)    

    EventSystem::Create();

    StartEvent* se = new StartEvent();
	StopEvent ste;
    PayLoadEvent* pe = new PayLoadEvent();

	auto sm = StateMachine::Create("Main");
	sm->AddEventHandler(StartEvent::Id, HelloWorld);

    auto ap = sm->GetReference();
    EventSystem::Get()->RegisterStateMachine(ap);
				
    EventSystem::Get()->RaiseEvent(se);	

    EventSystem::Get()->RaiseEvent(pe);
	
	std::cout << pe->GetMessage() << std::endl;
	
    EventSystem::Get()->RaiseEvent(pe);
	std::cout << pe->GetMessage() << std::endl;		

	volatile int countThisPass = pe->GetCounter();
	int waits = 0;
	while (pe->GetCounter() < 100)
	{        
        countThisPass = pe->GetCounter();
        pe->Reset();        
        EventSystem::Get()->RaiseEvent(pe);		
        EventSystem::Get()->RaiseEvent(nullptr);
		waits = 0;        
		while (countThisPass >= pe->GetCounter())
		{
			std::this_thread::sleep_for(std::chrono::microseconds(100));
			++waits;
		}
		
		std::cout << "Total waits on SM to process: " << waits << std::endl;		
	}
	
    EventSystem::Get()->RaiseEvent(&ste);

	while (!sm->HasExited())
	{
		std::cout << "Waiting for Sm to Exit" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

    delete pe;
    delete se;

    sm.reset();

		


	auto thing = std::make_shared<SomethingElse>();
	++thing->shared;

	std::weak_ptr<SomethingElse> weak = thing;
	++thing->shared;

	thing.reset();

	if (!weak.expired())
	{
		auto actual = weak.lock();
		++actual->shared;
		std::cout << actual->shared << std::endl;
	}
	


	/*A aa = A::One;
	int av = static_cast<int>(aa);

	av++;
	A bb = static_cast<A>(av);

	av++;
	A cc = static_cast<A>(av);*/




	std::vector<std::string> items
	{
		"Hello"
		//ReturnString("Hello World")
		//ReturnString("Yes"),
		//ReturnString("Missing has a space"),
		//ReturnString("No")
	};

	for (auto s : items)
	{
		std::cout << s << std::endl;
	}
	
	
	std::cout << "-----------------" << std::endl;

	LoadFileDataResultClass ec(LoadFileDataResultClass::Code::BufferCreationError);


	for (auto i{ LoadFileDataResultClass::Code::None }; i < LoadFileDataResultClass::Code::Maximum; ++i)
	{
		//std::cout << LoadFileDataResultClass::GetMessage(i) << std::endl;
	}	


	auto b = std::make_shared<Bar>();
	std::cout << "Uses: " << b.use_count() << std::endl;

	auto bp = b->GetShared();
	std::cout << "Uses: " << b.use_count() << std::endl;

	bp->Print();	
	std::cout << "Uses: " << b.use_count() << std::endl;

	auto bw = b->GetWeak();
	std::cout << "Uses: " << b.use_count() << std::endl;
	if (!bw.expired())
	{
		auto sp = bw.lock();
		std::cout << "Uses: " << b.use_count() << std::endl;
		sp->Print();		
	}
	std::cout << "Uses: " << b.use_count() << std::endl;

	//Error e;
	//std::cout << static_cast<int>(Error::Code::None) << std::endl;
	//std::cout << e.Message() << std::endl;
}