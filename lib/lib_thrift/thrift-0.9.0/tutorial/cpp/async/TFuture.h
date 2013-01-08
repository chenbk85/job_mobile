#ifndef _THRIFT_TCONTROLLER_H_
#define _THRIFT_TCONTROLLER_H_ 1

#include <boost/function.hpp>
#include <thrift/concurrency/Mutex.h>
#include <boost/shared_ptr.hpp>
#include <iostream>

namespace {
void warn(const char s[]) {
  std::cerr << "Warning: " << s << std::endl;
}
}

namespace apache { namespace thrift { namespace async {

/*********************** TController *****************/

template <typename result_t, typename success_t, typename success_constref_t>
class TBaseController {
 public:
  TBaseController() : executed_(false), has_success_(false), has_error_(false) { }
  TBaseController(success_constref_t success) : executed_(false), has_success_(true), has_error_(false) { result_.success = success; }
  TBaseController(const result_t& result) : executed_(false), has_success_(false), has_error_(true), result_(result) { }
  ~TBaseController() {
  }
  result_t &result() { return result_; }
  success_t &success() { return result_.success; }

  void callback() {
    concurrency::Guard g(mutex_);
    if (has_success_) warn("TController already has success");
    has_success_ = true;
    if (callback_) runCallback();
  }
  void errback() {
    concurrency::Guard g(mutex_);
    if (has_error_) warn("TController already has error");
    has_error_ = true;
    if (errback_) runErrback();
  }
  void callback(success_constref_t success) {  // shorthand for callback()
    concurrency::Guard g(mutex_);
    if (has_success_) warn("TController already has success");
    has_success_ = true;
    result_.success = success;
    if (callback_) runCallback();
  }
  void errback(const result_t &result) {  // shorthand for errback()
    concurrency::Guard g(mutex_);
    if (has_error_) warn("TController already has error");
    has_error_ = true;
    result_ = result;
    if (errback_) runErrback();
  }
  TBaseController<result_t, success_t, success_constref_t>& setCallback(boost::function<void (success_constref_t)> callback) {
    concurrency::Guard g(mutex_);
    if (callback_) warn("TController already has callback");
    callback_ = callback;
    if (has_success_) runCallback();
    return *this;
  }
  TBaseController<result_t, success_t, success_constref_t>& setErrback(boost::function<void (const result_t &)> errback) {
    concurrency::Guard g(mutex_);
    if (errback_) warn("TController already has errback");
    errback_ = errback;
    if (has_error_) runErrback();
    return *this;
  }
 private:
  void runCallback() { // Invoked as soon as there is both a success and a callback set
    if (executed_) warn("TController has already been executed");
    executed_ = true;
    callback_(result_.success);
  }
  void runErrback() { // Invoked as soon as there is both a success and a callback set
    if (executed_) warn("TController has already been executed");
    executed_ = true;
    errback_(result_);
  }
  bool has_success_, has_error_, executed_;
  result_t result_;
  boost::function<void (success_constref_t)> callback_;
  boost::function<void (const result_t&)> errback_;
  concurrency::Mutex mutex_;
};

template <typename result_t>
class TBaseController<result_t, void, void> {
 public:
  TBaseController() : executed_(false), has_success_(false), has_error_(false) { }
  TBaseController(bool success) : executed_(false), has_success_(true), has_error_(false) { }
  TBaseController(const result_t& result) : has_success_(false), has_error_(true), result_(result) {
    has_error_ = true;
  }
  ~TBaseController() {
    if (!executed_) warn("TController expired without being executed");
  }
  result_t &result() { return result_; }

  void callback() {
    concurrency::Guard g(mutex_);
    if (has_success_) warn("TController already has success");
    has_success_ = true;
    if (callback_) runCallback();
  }
  void errback() {
    concurrency::Guard g(mutex_);
    if (has_error_) warn("TController already has error");
    has_error_ = true;
    if (errback_) runErrback();
  }
  void errback(const result_t &result) {  // shorthand for errback()
    concurrency::Guard g(mutex_);
    if (has_error_) warn("TController already has error");
    has_error_ = true;
    result_ = result;
    if (errback_) runErrback();
  }
  TBaseController<result_t, void, void>& setCallback(boost::function<void (void)> callback) {
    concurrency::Guard g(mutex_);
    if (callback_) warn("TController already has callback");
    callback_ = callback;
    if (has_success_) runCallback();
    return *this;
  }
  TBaseController<result_t, void, void>& setErrback(boost::function<void (const result_t &)> errback) {
    concurrency::Guard g(mutex_);
    if (errback_) warn("TController already has errback");
    errback_ = errback;
    if (has_error_) runErrback();
    return *this;
  }
 private:
  void runCallback() { // Invoked as soon as there is both a success and a callback set
    if (executed_) warn("TController has already been executed");
    executed_ = true;
    callback_();
  }
  void runErrback() { // Invoked as soon as there is both a success and a callback set
    if (executed_) warn("TController has already been executed");
    executed_ = true;
    errback_(result_);
  }
  bool has_success_, has_error_, executed_;
  result_t result_;
  boost::function<void (void)> callback_;
  boost::function<void (result_t)> errback_;
  concurrency::Mutex mutex_;
};

template <typename result_t>
class TController : public TBaseController<result_t, typename result_t::success_t, typename result_t::success_constref_t> {
  // success_constref_t is equal to:
  // - success_t          when success_t is plain old data (such as int, bool etc.)
  // - const success_t&   when success_t is a complex type (i.e. user-defined structs)
  //
  // success_nonvoid_t is equal to:
  // - success_t          when success_t is not void
  // - bool               when success_t is void
  //
  // success_constref_nonvoid_t is equal to:
  // - success_constref_t when success_t is not void
  // - bool               when success_t is void
 public:
  TController() : TBaseController<result_t, typename result_t::success_t, typename result_t::success_constref_t>() {}
  TController(typename result_t::success_constref_nonvoid_t success) : TBaseController<result_t, typename result_t::success_t, typename result_t::success_constref_t>(success) {}
  TController(const result_t& result) : TBaseController<result_t, typename result_t::success_t, typename result_t::success_constref_t>(result) {}
};

/*********************** TSharedPromise *****************/

template<typename result_t, typename success_t, typename success_constref_t> class TBaseSharedFuture; // fwd declaration for friend class

template <typename result_t, typename success_t, typename success_constref_t>
class TBaseSharedPromise {
  friend class TBaseSharedFuture<result_t, success_t, success_constref_t>; // needs to touch its p_
 public:
  TBaseSharedPromise() : p_(new TController<result_t>) {}
  TBaseSharedPromise(const TBaseSharedPromise& rhs) : p_(rhs.p_) {}
  TBaseSharedPromise(const result_t& result) : p_(new TController<result_t>(result)) {}
  TBaseSharedPromise(success_constref_t success) : p_(new TController<result_t>(success)) {}

  void callback() { p_->callback(); }
  void errback() { p_->errback(); }
  void callback(success_constref_t success) { p_->callback(success); }
  void errback(const result_t& result) { p_->errback(result); }
  result_t& result() { return p_->result(); }
  success_t& success() { return p_->success(); }

 private:
  boost::shared_ptr<TController<result_t> > p_;
};

template <typename result_t>
class TBaseSharedPromise<result_t, void, void> {
  friend class TBaseSharedFuture<result_t, void, void>; // needs to touch its p_
 public:
  TBaseSharedPromise() : p_(new TController<result_t>) {}
  TBaseSharedPromise(const TBaseSharedPromise& rhs) : p_(rhs.p_) {}
  TBaseSharedPromise(const result_t& result) : p_(new TController<result_t>(result)) {}
  TBaseSharedPromise(bool success) : p_(new TController<result_t>(success)) {}

  void callback() { p_->callback(); }
  void errback() { p_->errback(); }
  void errback(const result_t& result) { p_->errback(result); }
  result_t& result() { return p_->result(); }

 private:
  boost::shared_ptr<TController<result_t> > p_;
};

template <typename result_t>
class TSharedPromise : public TBaseSharedPromise<result_t, typename result_t::success_t, typename result_t::success_constref_t> {
 public:
  TSharedPromise() : TBaseSharedPromise<result_t, typename result_t::success_t, typename result_t::success_constref_t>() {}
  TSharedPromise(typename result_t::success_constref_nonvoid_t success) : TBaseSharedPromise<result_t, typename result_t::success_t, typename result_t::success_constref_t>(success) {}
  TSharedPromise(const result_t& result) : TBaseSharedPromise<result_t, typename result_t::success_t, typename result_t::success_constref_t>(result) {}
};

/*********************** TSharedFuture *****************/

template <typename result_t, typename success_t, typename success_constref_t>
class TBaseSharedFuture {
 public:
  //  TBaseSharedFuture() : p_(new TController<result_t>) {}
  TBaseSharedFuture(const TBaseSharedFuture& rhs) : p_(rhs.p_) {}
  TBaseSharedFuture(const TSharedPromise<result_t>& rhs) : p_(rhs.p_) {}
  TBaseSharedFuture(const result_t& result) : p_(new TController<result_t>(result)) {}
  TBaseSharedFuture(success_constref_t success) : p_(new TController<result_t>(success)) {}

  TBaseSharedFuture<result_t, success_t, success_constref_t>& setCallback(boost::function<void (success_constref_t)> callback) { p_->setCallback(callback); return *this; }
  TBaseSharedFuture<result_t, success_t, success_constref_t>& setErrback(boost::function<void (const result_t &)> errback) { p_->setErrback(errback); return *this; }
 private:
  boost::shared_ptr<TController<result_t> > p_;
};

template <typename result_t>
class TBaseSharedFuture<result_t, void, void> {
 public:
  //  TBaseSharedFuture() : p_(new TController<result_t>) {}
  TBaseSharedFuture(const TBaseSharedFuture& rhs) : p_(rhs.p_) {}
  TBaseSharedFuture(const TSharedPromise<result_t>& rhs) : p_(rhs.p_) {}
  TBaseSharedFuture(const result_t& result) : p_(new TController<result_t>(result)) {}
  TBaseSharedFuture(bool success) : p_(new TController<result_t>(success)) {}
  TBaseSharedFuture<result_t, void, void>& setCallback(boost::function<void ()> callback) { p_->setCallback(callback); return *this; }
  TBaseSharedFuture<result_t, void, void>& setErrback(boost::function<void (const result_t &)> errback) { p_->setErrback(errback); return *this; }
 private:
  boost::shared_ptr<TController<result_t> > p_;
};

template <typename result_t>
class TSharedFuture : public TBaseSharedFuture<result_t, typename result_t::success_t, typename result_t::success_constref_t> {
 public:
  //  TSharedFuture() : TBaseSharedFuture<result_t, typename result_t::success_t, typename result_t::success_constref_t>() {}
  TSharedFuture(const TSharedPromise<result_t>& rhs) : TBaseSharedFuture<result_t, typename result_t::success_t, typename result_t::success_constref_t>(rhs) {}
  TSharedFuture(typename result_t::success_constref_nonvoid_t success) : TBaseSharedFuture<result_t, typename result_t::success_t, typename result_t::success_constref_t>(success) {}
  TSharedFuture(const result_t& result) : TBaseSharedFuture<result_t, typename result_t::success_t, typename result_t::success_constref_t>(result) {}
};

} } }; // end namespaces

#endif
