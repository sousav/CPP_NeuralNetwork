/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   29/04/2018 20:10:29
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 29/04/2018 20:27:25
 */


#ifndef NETWORKEXCEPTION
#define NETWORKEXCEPTION

#include <string>

namespace Neural {

    class NetworkException : public std::exception {
    public:
        NetworkException(std::string const &message) {
            _message = message;
        };

        virtual ~NetworkException() throw() {};

        virtual const char *what(void) const throw() {
            return (this->_message.data());
        }

    private:
        std::string _message;
    };

    class InvalidInput : public NetworkException {

    public:
        InvalidInput(std::string const &message) : NetworkException(message) {};

        virtual ~InvalidInput() throw() {};

    };

    class InvalidTrainingFile : public NetworkException {

    public:
        InvalidTrainingFile(std::string const &message) : NetworkException(message) {};

        virtual ~InvalidTrainingFile() throw() {};

    };

    class InvalidSavingFile : public NetworkException {

    public:
        InvalidSavingFile(std::string const &message) : NetworkException(message) {};

        virtual ~InvalidSavingFile() throw() {};

    };

}

#endif /*NETWORKEXCEPTION*/
