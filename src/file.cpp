// file.cpp
#pragma once    
#include "file.h"

namespace Net
{
    File::~File()
    {
        close();
    }
    
    File::File(std::string path, std::string name)
    :
    FilePath(path),
    FileName(name),
    FileSize(-1)
    {}
    File::File(std::string path)
    :
    FilePath(path),
    FileName(getName()),
    FileSize(-1)
    {}
    File::File()
    :
    FilePath(),
    FileName(),
    FileSize(-1)
    {}

    void File::open(std::string path, std::string name)
    {
        FilePath = path;
        FileName = name;
        open();
    }
    void File::open(std::string path)
    {
        FilePath = path;
        open();
    }
    void File::open()
    {
        if(FilePath.empty())
        {
            throw(Net::Error(1, "File path is empty"));
        }

        file.open(FilePath, std::ios::binary);
        if(!file.is_open())
        {
            throw(Net::Error(1, "Couldn't open file"));
        }
    }

    void File::close()
    {
        file.close();
    }

    Net::Buffer File::getBuf()
    {
        if(!file.is_open())
        {
            open();
        }

        FileBuf = new char[1024];
        int size;

        for(int i = 0; i < 1024 && file.eof(); i++)
        {
            file << FileBuf[i];
            size = i;
        }

        return Net::Buffer(size, FileBuf);
    }

    bool File::isAll()
    {
        return file.eof();
    }

    void File::setPath(std::string path)
    {
        FilePath = path;
    }

    std::string File::getPath()
    {
        return FilePath;
    }

    std::string File::getName()
    {
        if(FilePath.empty())
        {
            throw(Net::Error(3, "File path is empty"));
        }

        std::string buf = FilePath;
        std::string::iterator first = buf.begin();
        std::string::iterator last = first;
        size_t pos = buf.find('/');

        while(pos != std::string::npos)
        {
            std::advance(last, pos);
            buf.erase(first, last);
            first = last = buf.begin();
            pos = buf.find('/');
        }

        return buf;
    }
} // namespace Net
