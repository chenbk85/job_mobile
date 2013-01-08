#include "backend_handler.hpp"
#include "backend.hpp"
#include "backend_room.hpp"
#include "presence.pb.h"

#include <boost/program_options/option.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>

#include <iostream>
#include <boost/signals2.hpp>

#include <boost/thread.hpp>
#include <boost/any.hpp>
#include <boost/asio.hpp>

#include <boost/thread/future.hpp>
#include <boost/make_shared.hpp>

namespace po = boost::program_options;

static int num_threads_per_op = 1;

namespace
{
    class DelayedStartThread
    {
    private:
        int id_;
        PReqProtocol req_;
        PAnsProtocol ans_;
        BackEndModuleRoom * bem_;

        void Run(int i, PReqProtocol & fake_req, PAnsProtocol & fake_ans, BackEndModuleRoom * bem)
            { 
                boost::shared_ptr<presence::SKSK> entry_func = bem->entry_point;
       
                std::cout << "[" << boost::this_thread::get_id() 
                          << "]Sending(" << i << ") with op=" 
                          << fake_req.command() << "|" << fake_req.gameid() << std::endl;

                presence::SpGameService service = boost::shared_ptr<presence::GameService>();

                boost::promise<int> retval;
                boost::unique_future<int> fi(retval.get_future());

                entry_func->dispatcher_.post(
                    boost::bind(entry_func->handler_, (void *)&fake_req, (void *)&fake_ans, service, &retval)
                    );
                fi.wait();
                assert(fi.is_ready());
                assert(fi.has_value());
                assert(!fi.has_exception());
                assert(fi.get_state()==boost::future_state::ready);

                std::cout << "[" << boost::this_thread::get_id() 
                          << "]Got result for(" << i << ") with op=" 
                          << fake_req.command() << "|" << fake_req.gameid() << "(" 
                          << fake_ans.info() << ")" << std::endl;
            }

    public:
        boost::thread * t_;

        DelayedStartThread(int i, PReqProtocol & fake_req, PAnsProtocol & fake_ans, BackEndModuleRoom * bem) : 
            id_(i), req_(fake_req), ans_(fake_ans), bem_(bem)
            {
                t_ = NULL;
            }

        void start()
            {
                t_ = new boost::thread(&DelayedStartThread::Run, this, id_, req_, ans_, bem_);
            }

        void join()
            {
                t_->join();
            }

    };

    bool parseOptions(int ac, char *av[])
    {
        // Declare the supported options.
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help", "produce help message")
            ("nt", po::value<int>(), "set number of threads per op")
            ;
    
        po::variables_map vm;
        po::store(po::parse_command_line(ac, av, desc), vm);
        po::notify(vm);    
    
        if (vm.count("help")) {
            std::cout << desc << "\n";
            return false;
        }
    
        if (vm.count("nt")) {
            std::cout << "Number of threads was set to " << vm["nt"].as<int>() << ".\n";
            num_threads_per_op = vm["nt"].as<int>();
        } else {
            std::cout << "Number of threads was not set. Defaulting to " << num_threads_per_op << "\n";
        }
        return true;
    }
}

int main(int argc, char *argv[])
{
    if (!parseOptions(argc, argv)) return 0;
    BackEndModuleRoom bem;
    presence::BackEnd be; // main server backbone
    be.initialize(bem);

    std::cout << "[" << boost::this_thread::get_id() 
              << "] main: module init DONE" << std::endl;
    
    std::vector<PReqProtocol> req_array1(num_threads_per_op);
    std::vector<PAnsProtocol> resp_array1(num_threads_per_op);
    std::vector<PReqProtocol> req_array2(num_threads_per_op);
    std::vector<PAnsProtocol> resp_array2(num_threads_per_op);

    for (int i=0; i < num_threads_per_op; ++i)
    {
        req_array1[i].set_gameid(i);
        req_array1[i].set_command((PresenceCommand)1);
        DelayedStartThread ts(i, req_array1[i], resp_array1[i], &bem);
        ts.start();
    }
  
    for (int i=0; i < num_threads_per_op; ++i)
    {
        req_array2[i].set_gameid(i);
        req_array2[i].set_command((PresenceCommand)3);
        DelayedStartThread ts(i, req_array2[i], resp_array2[i], &bem);
        ts.start();
    }

    std::cout << "[" << boost::this_thread::get_id() 
              << "] main: all client threads sent" << std::endl;
  
    sleep(100);
  
    return 0;
}
