//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Part 2 - Homework 2
//Notes or Remarks:

#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <map>

using namespace std;

class Element
{
public:
    string name;
    map<string, string> attributes;
    vector<Element> children;
    string textContent;

    Element *findChildByName(const string &tagName)
    {
        for (auto &child : children)
        {
            if (child.name == tagName)
            {
                return &child;
            }
        }
        return NULL;
    }

    vector<Element *> findChildrenByName(const string &tagName)
    {
        vector<Element *> results;
        for (auto &child : children)
        {
            if (child.name == tagName)
            {
                results.push_back(&child);
            }
        }
        return results;
    }

    Element *findElementByNameRecursive(const string &tagName)
    {
        if (this->name == tagName)
        {
            return this;
        }
        for (auto &child : children)
        {
            Element *found = child.findElementByNameRecursive(tagName);
            if (found)
                return found;
        }
        return NULL;
    }
    string getAttribute(const string &attrName) const
    {
        auto it = attributes.find(attrName);
        if (it != attributes.end())
        {
            return it->second;
        }
        return "";
    }
};

class Parser
{
public:
    Element parse(const string &input)
    {
        this->input = input;
        pos = 0;
        skipWhitespace();
        Element root = parseElement();
        return root;
    }

private:
    string input;
    size_t pos = 0;
    bool end() const
    {
        return pos >= input.size();
    }
    char current() const
    {
        if (end())
            return '\0';
        return input[pos];
    }
    char next()
    {
        if (!end())
            pos++;
        return current();
    }

    void skipWhitespace()
    {
        while (!end() && isspace(static_cast<unsigned char>(current())))
        {
            next();
        }
    }

    Element parseElement()
    {
        Element elem;
        if (current() != '<')
        {
            elem.textContent = parseText();
            return elem;
        }
        next();
        elem.name = parseTagName();
        skipWhitespace();
        while (current() != '>' && current() != '/' && !end())
        {
            parseAttribute(elem.attributes);
            skipWhitespace();
        }
        if (current() == '/')
        {
            next();
            if (current() == '>')
            {
                next();
            }
            return elem;
        }
        else if (current() == '>')
        {
            next();
            parseContent(elem);

            if (current() == '<' && peekNext() == '/')
            {
                next();
                next();
                string endTag = parseTagName();
                skipWhitespace();
                if (current() == '>')
                {
                    next();
                }
            }
        }
        return elem;
    }

    string parseTagName()
    {
        string tagName;
        while (!end() && (isalnum(static_cast<unsigned char>(current())) || current() == '-' || current() == '_'))
        {
            tagName.push_back(current());
            next();
        }
        return tagName;
    }

    void parseAttribute(map<string, string> &attributes)
    {
        string attrName = parseAttributeName();
        skipWhitespace();
        string attrValue;
        if (current() == '=')
        {
            next();
            skipWhitespace();
            attrValue = parseAttributeValue();
        }
        attributes[attrName] = attrValue;
    }

    string parseAttributeName()
    {
        string name;
        while (!end() && (isalnum(static_cast<unsigned char>(current())) || current() == '-' || current() == '_'))
        {
            name.push_back(current());
            next();
        }
        return name;
    }

    string parseAttributeValue()
    {
        string value;
        if (current() == '"' || current() == '\'')
        {
            char quote = current();
            next();
            while (!end() && current() != quote)
            {
                value.push_back(current());
                next();
            }
            if (current() == quote)
            {
                next();
            }
        }
        else
        {
            while (!end() && !isspace(static_cast<unsigned char>(current())) && current() != '>' && current() != '/')
            {
                value.push_back(current());
                next();
            }
        }
        return value;
    }

    void parseContent(Element &elem)
    {
        skipWhitespace();
        while (!end())
        {
            if (current() == '<')
            {
                if (peekNext() == '/')
                {
                    break;
                }

                Element child = parseElement();
                if (!child.name.empty() || !child.textContent.empty())
                {
                    elem.children.push_back(child);
                }
            }
            else
            {
                string text = parseText();
                if (!text.empty())
                {
                    elem.textContent += text;
                }
            }
            skipWhitespace();
        }
    }

    string parseText()
    {
        string text;
        while (!end() && current() != '<')
        {
            text.push_back(current());
            next();
        }
        return text;
    }

    // Peek next character without consuming
    char peekNext() const
    {
        if (pos + 1 < input.size())
            return input[pos + 1];
        return '\0';
    }
};

int main()
{
    string xml = R"(
<root>
    <title>Hello World</title>
    <body>
        <h1 class="header" id="main-title">Welcome</h1>
        <p>Some paragraph text <b>bold</b>.</p>
    </body>
</root>
)";

    Parser parser;
    Element root = parser.parse(xml);

    cout << "Root element: " << root.name << "\n";

    Element *title = root.findElementByNameRecursive("title");
    if (title)
    {
        cout << "Title text: " << title->textContent << "\n";
    }

    Element *h1 = root.findElementByNameRecursive("h1");
    if (h1)
    {
        cout << "H1 text: " << h1->textContent << "\n";
        cout << "H1 class attribute: " << h1->getAttribute("class") << "\n";
        cout << "H1 id attribute: " << h1->getAttribute("id") << "\n";
    }

    Element *bold = root.findElementByNameRecursive("b");
    if (bold)
    {
        cout << "Bold text: " << bold->textContent << "\n";
    }

    return 0;
}

