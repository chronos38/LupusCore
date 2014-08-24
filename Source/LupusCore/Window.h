#pragma once

#include "Utility.h"
#include "Event.h"
#include "Observable.h"
#include "Size.h"
#include "Point.h"
#include "Rectangle.h"

#include <unordered_map>
#include <boost/noncopyable.hpp>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    namespace Windows {
        enum class WindowFlags {
            None = LupusNoFlag,
            Fullscreen = LupusFlagNumber(0),
            FullscreenDesktop = LupusFlagNumber(1),
            Shown = LupusFlagNumber(2),
            Hidden = LupusFlagNumber(3),
            Borderless = LupusFlagNumber(4),
            Resizable = LupusFlagNumber(5),
            Minimized = LupusFlagNumber(6),
            Maximized = LupusFlagNumber(7),
            InputGrabbed = LupusFlagNumber(8),
            InptuFocus = LupusFlagNumber(9),
            MouseFocus = LupusFlagNumber(10),
            AllowHighDPI = LupusFlagNumber(11)
        };
        LupusFlagEnumeration(WindowFlags);

        // TODO: Schnittstelle ausbauen und Klasse implementieren.
        class LUPUS_API Window : public boost::noncopyable
        {
        public:
            template <typename... Args>
            using WindowEvent = Event < Window, Args... > ;

            template <typename T>
            using WindowProperty = ObservableProperty < Window, T > ;

            Window(WindowFlags flags = WindowFlags::None) throw(std::runtime_error);
            Window(int x, int y, WindowFlags flags = WindowFlags::None) throw(std::runtime_error);
            Window(int x, int y, int w, int h, WindowFlags flags = WindowFlags::None) throw(std::runtime_error);
            Window(const Math::Point<int>& position, WindowFlags flags = WindowFlags::None) throw(std::runtime_error);
            Window(const Math::Point<int>& position, const Math::Size<int>& size, WindowFlags flags = WindowFlags::None) throw(std::runtime_error);
            Window(const Math::Rectangle<int>& rect, WindowFlags flags = WindowFlags::None) throw(std::runtime_error);
            virtual ~Window();

            // Properties

            ObservableProperty<void, std::string> Uid;
            WindowProperty<std::string> Title;
            WindowProperty<float> Brightness;
            WindowProperty<bool> Grabbed;
            WindowProperty<Math::Size<int>> MaxSize;
            WindowProperty<Math::Size<int>> MinSize;
            WindowProperty<Math::Size<int>> Size;
            WindowProperty<Math::Point<int>> Position;
            WindowProperty<Math::Rectangle<int>> Rectangle;

            // Methods

            virtual void Bordered(bool) const final;
            virtual int DisplayIndex() const final;
            virtual void Hide() final;
            virtual void Maximize() final;
            virtual void Minimize() final;
            virtual void Raise() final;
            virtual void Restore() final;
            virtual void Show() final;
            virtual void ShowDialog() final;
            virtual void Refresh() throw(std::runtime_error) final;

            // Events

            //! Fenster ist sichtbar.
            WindowEvent<> Shown;
            //! Fenster ist nicht mehr sichtbar.
            WindowEvent<> Hidden;
            //! Fenster sollte neu gezeichnet werden.
            WindowEvent<> Exposed;
            //! Fenster wurde bewegt.
            WindowEvent<> Moved;
            //! Fenstergröße wurde verändert.
            WindowEvent<> Resized;
            //! Fentergröße hat sich verändert, wird nach Resized aufgerufen.
            WindowEvent<> SizeChanged;
            //! Fenster wurde minimiert.
            WindowEvent<> Minimized;
            //! Fenster wurde maximiert.
            WindowEvent<> Maximized;
            //! Fenster hat wieder Normalgröße.
            WindowEvent<> Restored;
            //! Fenster hat jetzt Mausfokus.
            WindowEvent<> Enter;
            //! Fenster hat keinen Mausfokus mehr.
            WindowEvent<> Leave;
            //! Fenster hat jetzt Tastaturfokus.
            WindowEvent<> FocuesGained;
            //! Fenster hat Tastarufokus verloren.
            WindowEvent<> FocusLost;
            //! Fenster soll geschlossen werden.
            WindowEvent<> Close;

            static Window* GetWindowFromId(uint32_t);

            static const int PositionCentered;
            static const int PositionUndefined;

        private:

            uint32_t ConvertFlags(WindowFlags flags);
            void SetPropertyHandles();

            void* mHandle = nullptr;
            static std::unordered_map<uint32_t, Window*> smMappedWindows;
        };
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
