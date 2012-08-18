/*! \file
    \brief The definition of tetengo2::detail::windows::direct2d::drawing.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_DIRECT2D_DRAWING_H)
#define TETENGO2_DETAIL_WINDOWS_DIRECT2D_DRAWING_H

//#include <cassert>
//#include <cstddef>
//#include <memory>
//#include <stdexcept>
//#include <string>
//#include <system_error>
#include <tuple>
//#include <utility>

//#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/scope_exit.hpp>
//#include <boost/throw_exception.hpp>

#pragma warning (push)
#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h>
#pragma warning(pop)
//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>
//#include <d2d1.h>
#include <dwrite.h>
#include <dxgiformat.h>
//#include <Unknwn.h>

#include "tetengo2.detail.windows.com_ptr.h"
#include "tetengo2.detail.windows.direct2d.error_category.h"
#include "tetengo2.detail.windows.font.h"
#include "tetengo2.detail.windows.picture.h"
#include "tetengo2.gui.measure.h"
#include "tetengo2.unique.h"


namespace tetengo2 { namespace detail { namespace windows { namespace direct2d
{
#if !defined(DOCUMENTATION)
    namespace detail
    {
        // types

        struct release_render_target
        {
            void operator()(::ID2D1RenderTarget* p_render_target)
            const
            {
                if (p_render_target)
                {
                    const ::HRESULT hr = p_render_target->EndDraw();
                    if (hr == D2DERR_RECREATE_TARGET)
                    {
                        assert(false);
                    }
                    p_render_target->Release();
                    p_render_target = NULL;
                }
            }

        };

        class background_details : boost::noncopyable
        {
        public:
            virtual ~background_details()
            {}
        

        };

        class solid_background_details : public background_details
        {
        public:
            solid_background_details(
                const unsigned char red,
                const unsigned char green,
                const unsigned char blue,
                const unsigned char alpha
            )
            :
            m_red(red),
            m_green(green),
            m_blue(blue),
            m_alpha(alpha)
            {}

            virtual ~solid_background_details()
            {}

            unsigned char red()
            const
            {
                return m_red;
            }

            unsigned char green()
            const
            {
                return m_green;
            }

            unsigned char blue()
            const
            {
                return m_blue;
            }

            unsigned char alpha()
            const
            {
                return m_alpha;
            }


        private:
            const unsigned char m_red;

            const unsigned char m_green;

            const unsigned char m_blue;

            const unsigned char m_alpha;

        };
    }
#endif


    /*!
        \brief The class for a detail implementation of a drawing.
    */
    class drawing : private boost::noncopyable
    {
    public:
        // types

        //! The background details type.
        typedef detail::background_details background_details_type;

        //! The background details pointer type.
        typedef std::unique_ptr<background_details_type> background_details_ptr_type;

        //! The picture details type.
        typedef picture::details_type picture_details_type;

        //! The picture details pointer type.
        typedef picture::details_ptr_type picture_details_ptr_type;

        //! The canvas details type.
        typedef ::ID2D1RenderTarget canvas_details_type;

        //! The canvas details pointer type.
        typedef std::unique_ptr<canvas_details_type, detail::release_render_target> canvas_details_ptr_type;


        // static functions

        /*!
            \brief Creates a canvas.

            \tparam WidgetDetails A widget details type.

            \param widget_details A widget details.

            \return A unique pointer to a canvas.
        */
        template <typename WidgetDetails>
        static canvas_details_ptr_type create_canvas(const WidgetDetails& widget_details)
        {
            const ::HWND window_handle = std::get<0>(widget_details).get();

            ::D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties();
            props.pixelFormat = D2D1::PixelFormat(::DXGI_FORMAT_B8G8R8A8_UNORM, ::D2D1_ALPHA_MODE_PREMULTIPLIED);
            props.usage = ::D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE;

            ::D2D1_HWND_RENDER_TARGET_PROPERTIES hwnd_props = {};
            {
                ::RECT rect = {};
                const ::BOOL result = ::GetClientRect(window_handle, &rect);
                if (result == 0)
                {
                    BOOST_THROW_EXCEPTION(
                        std::system_error(
                            std::error_code(::GetLastError(), win32_category()), "Can't get client rectangle."
                        )
                    );
                }
                hwnd_props =
                    D2D1::HwndRenderTargetProperties(
                        window_handle, D2D1::SizeU(rect.right - rect.left, rect.bottom - rect.top)
                    );
            }

            ::ID2D1HwndRenderTarget* rp_render_target = NULL;
            const ::HRESULT hr = direct2d_factory().CreateHwndRenderTarget(props, hwnd_props, &rp_render_target);
            if (FAILED(hr))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(hr, direct2d_category()), "Can't create HWND render target.")
                );
            }
            std::unique_ptr< ::ID2D1HwndRenderTarget, detail::release_render_target> p_render_target(rp_render_target);

            p_render_target->BeginDraw();
            p_render_target->Clear(colorref_to_color_f(::GetSysColor(COLOR_3DFACE)));

            return canvas_details_ptr_type(std::move(p_render_target));
        }

        /*!
            \brief Creates a solid background.

            \tparam Color A color type.

            \param color A color.

            \return A unique pointer to a solid background.
        */
        template <typename Color>
        static background_details_ptr_type create_solid_background(const Color& color)
        {
            return
                tetengo2::make_unique<detail::solid_background_details>(
                    color.red(), color.green(), color.blue(), color.alpha()
                );
        }

        /*!
            \brief Creates a transparent background.

            \return A unique pointer to a transparent background.
        */
        static background_details_ptr_type create_transparent_background()
        {
            return background_details_ptr_type();
        }

        /*!
            \brief Creates a picture.

            \tparam Dimension A dimension type.

            \param dimension A dimension.

            \return A unique pointer to a picture.
        */
        template <typename Dimension>
        static picture_details_ptr_type create_picture(const Dimension& dimension)
        {
            return picture::create(dimension);
        }

        /*!
            \brief Reads a picture.

            \tparam Path A path type.

            \param path A path.

            \return A unique pointer to a picture.

            \throw std::system_error When the picture cannot be read.
        */
        template <typename Path>
        static picture_details_ptr_type read_picture(const Path& path)
        {
            return picture::read(path);
        }

        /*!
            \brief Returns the dimension of a picture.

            \tparam Dimension A dimension type.

            \param picture A picture.

            \return The dimension of the picture.
        */
        template <typename Dimension>
        static Dimension picture_dimension(const picture_details_type& picture)
        {
            return picture::dimension<Dimension>(picture);
        }

        /*!
            \brief Draws a line.

            \tparam Position A position type.
            \tparam Size     A size type.
            \tparam Color    A color type.

            \param canvas A canvas.
            \param from   A beginning position.
            \param to     An ending position.
            \param width  A width.
            \param style  A style.
            \param color  A color.
        */
        template <typename Position, typename Size, typename Color>
        static void draw_line(
            canvas_details_type& canvas,
            const Position&      from,
            const Position&      to,
            const Size           width,
            const int            style,
            const Color&         color
        )
        {
            const background_details_ptr_type p_background_details = create_solid_background(color);
            const typename unique_com_ptr< ::ID2D1Brush>::type p_brush = create_brush(canvas, *p_background_details);
            const typename unique_com_ptr< ::ID2D1StrokeStyle>::type p_stroke_style =
                create_stroke_style(style);
            canvas.DrawLine(
                position_to_point_2f(from),
                position_to_point_2f(to),
                p_brush.get(),
                size_to_float(width),
                p_stroke_style.get()
            );
        }

        /*!
            \brief Draws a focus indication.

            \tparam Position  A position type.
            \tparam Dimension A dimension type.

            \param canvas    A canvas.
            \param position  A position of a region.
            \param dimension A dimension of a region.

            \throw std::system_error When the focus indication cannot be drawn.
        */
        template <typename Position, typename Dimension>
        static void draw_focus_indication(
            canvas_details_type& canvas,
            const Position&      position,
            const Dimension&     dimension
        );

        /*!
            \brief Fills a rectangle region.

            \tparam Position   A position type.
            \tparam Dimension  A dimension type.
            \tparam Background A background type.

            \param canvas     A canvas.
            \param position   A position of a region.
            \param dimension  A dimension of a region.
            \param background A background.

            \throw std::system_error When the rectangle cannot be filled.
        */
        template <typename Position, typename Dimension, typename Background>
        static void fill_rectangle(
            canvas_details_type& canvas,
            const Position&      position,
            const Dimension&     dimension,
            const Background&    background
        )
        {
            const boost::optional<const typename Background::details_type&> background_details = background.details();
            if (!background_details) return;

            const typename unique_com_ptr< ::ID2D1Brush>::type p_brush = create_brush(canvas, *background_details);

            canvas.FillRectangle(position_and_dimension_to_rect_f(position, dimension), p_brush.get());
        }

        /*!
            \brief Makes a dialog font.

            \tparam Font A font type.

            \return A dialog font.
        */
        template <typename Font>
        static Font make_dialog_font()
        {
            const ::LOGFONTW log_font = get_message_font();

            assert(log_font.lfHeight < 0);
            return
                Font(
                    log_font.lfFaceName,
                    -log_font.lfHeight,
                    log_font.lfWeight >= FW_BOLD,
                    log_font.lfItalic != 0,
                    log_font.lfUnderline != 0,
                    log_font.lfStrikeOut != 0
                );
        }

        /*!
            \brief Calculates the dimension of a text.

            \tparam Dimension A dimension type.
            \tparam Font      A font type.
            \tparam String    A string type.
            \tparam Encoder   An encoder type.

            \param canvas  A canvas.
            \param font    A font.
            \param text    A text.
            \param encoder An encoder.

            \return The dimension of the text.

            \throw std::system_error When the dimention of a text cannot be calculated.
        */
        template <typename Dimension, typename Font, typename String, typename Encoder>
        static Dimension calc_text_dimension(
            const canvas_details_type& canvas,
            const Font&                font,
            const String&              text,
            const Encoder&             encoder
        )
        {
            const typename unique_com_ptr< ::IDWriteTextLayout>::type p_layout =
                create_text_layout(text, font, encoder);

            ::DWRITE_TEXT_METRICS metrics = {};
            const ::HRESULT get_metrics_hr = p_layout->GetMetrics(&metrics);
            if (FAILED(get_metrics_hr))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(get_metrics_hr, win32_category()), "Can't get text metrics.")
                );
            }

            return
                Dimension(
                    gui::to_unit<typename gui::dimension<Dimension>::width_type>(metrics.width),
                    gui::to_unit<typename gui::dimension<Dimension>::height_type>(metrics.height)
                );
        }

        /*!
            \brief Draws a text.

            \tparam Font     A font type.
            \tparam String   A string type.
            \tparam Encoder  An encoder type.
            \tparam Position A position type.
            \tparam Color    A color type.

            \param canvas   A canvas.
            \param font     A font.
            \param text     A text to draw.
            \param encoder  An encoder.
            \param position A position where the text is drawn.
            \param color    A color.
            \param angle    A clockwise angle in radians.

            \throw std::system_error When the text cannot be drawn.
        */
        template <typename Font, typename String, typename Encoder, typename Position, typename Color>
        static void draw_text(
            canvas_details_type& canvas,
            const Font&          font,
            const String&        text,
            const Encoder&       encoder,
            const Position&      position,
            const Color&         color,
            const double         angle
        )
        {
            const typename unique_com_ptr< ::IDWriteTextLayout>::type p_layout =
                create_text_layout(text, font, encoder);

            const background_details_ptr_type p_background_details = create_solid_background(color);
            const typename unique_com_ptr< ::ID2D1Brush>::type p_brush = create_brush(canvas, *p_background_details);

            ::D2D1_MATRIX_3X2_F original_transform = D2D1::Matrix3x2F();
            canvas.GetTransform(&original_transform);
            BOOST_SCOPE_EXIT((&canvas)(&original_transform))
            {
                canvas.SetTransform(original_transform);
            } BOOST_SCOPE_EXIT_END;
            ::D2D1_MATRIX_3X2_F rotating_transform =
                D2D1::Matrix3x2F::Rotation(radian_to_degree(angle), position_to_point_2f(position));
            canvas.SetTransform(rotating_transform);

            canvas.DrawTextLayout(position_to_point_2f(position), p_layout.get(), p_brush.get());
        }

        /*!
            \brief Paints a picture.

            \tparam Picture   A picture type.
            \tparam Position  A position type.
            \tparam Dimension A dimension type.

            \param canvas    A canvas.
            \param picture   A picture to paint.
            \param position  A position where the picture is painted.
            \param dimension A dimension in which the picture is painted.

            \throw std::system_error When the picture cannot be painted.
        */
        template <typename Picture, typename Position, typename Dimension>
        static void paint_picture(
            canvas_details_type& canvas,
            const Picture&       picture,
            const Position&      position,
            const Dimension&     dimension
        )
        {
            const boost::optional<typename Picture::details_type&> picture_details(
                const_cast<Picture&>(picture).details()
            );
            if (!picture_details) return;

            ::ID2D1Bitmap* rp_bitmap = NULL;
            const ::HRESULT create_bitmap_hr =
                canvas.CreateBitmapFromWicBitmap(&*picture_details, &rp_bitmap);
            if (FAILED(create_bitmap_hr))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(create_bitmap_hr, direct2d_category()), "Can't create bitmap.")
                );
            }
            const typename unique_com_ptr< ::ID2D1Bitmap>::type p_bitmap(rp_bitmap);

            canvas.DrawBitmap(p_bitmap.get(), position_and_dimension_to_rect_f(position, dimension));
        }


    private:
        // types

        typedef unique_com_ptr< ::ID2D1Factory>::type direct2d_factory_ptr_type;

        typedef unique_com_ptr< ::IDWriteFactory>::type direct_write_factory_ptr_type;


        // static functions

        static ::ID2D1Factory& direct2d_factory()
        {
            static const direct2d_factory_ptr_type p_factory(create_direct2d_factory());
            return *p_factory;
        }

        static direct2d_factory_ptr_type create_direct2d_factory()
        {
            ::ID2D1Factory* rp_factory = NULL;
            const ::HRESULT hr = ::D2D1CreateFactory(::D2D1_FACTORY_TYPE_SINGLE_THREADED, &rp_factory);
            if (FAILED(hr))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(hr, direct2d_category()), "Can't create Direct2D factory.")
                );
            }

            return direct2d_factory_ptr_type(rp_factory);
        }

        static ::IDWriteFactory& direct_write_factory()
        {
            static const direct_write_factory_ptr_type p_factory(create_direct_write_factory());
            return *p_factory;
        }

        static direct_write_factory_ptr_type create_direct_write_factory()
        {
            ::IDWriteFactory* rp_factory = NULL;
            const ::HRESULT hr =
                ::DWriteCreateFactory(
                    ::DWRITE_FACTORY_TYPE_SHARED,
                    __uuidof(::IDWriteFactory),
                    reinterpret_cast< ::IUnknown**>(&rp_factory)
                );
            if (FAILED(hr))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(hr, win32_category()), "Can't create Direct Write factory.")
                );
            }

            return direct_write_factory_ptr_type(rp_factory);
        }

        template <typename Size>
        static ::FLOAT size_to_float(const Size size)
        {
            return gui::to_pixels< ::FLOAT>(size);
        }

        template <typename Position>
        static ::D2D1_POINT_2F position_to_point_2f(const Position& position)
        {
            const ::FLOAT left = gui::to_pixels< ::FLOAT>(gui::position<Position>::left(position));
            const ::FLOAT top = gui::to_pixels< ::FLOAT>(gui::position<Position>::top(position));
            return D2D1::Point2F(left - 0.5f, top - 0.5f);
        }

        template <typename Position, typename Dimension>
        static ::D2D1_RECT_F position_and_dimension_to_rect_f(const Position& position, const Dimension& dimension)
        {
            const ::FLOAT left = gui::to_pixels< ::FLOAT>(gui::position<Position>::left(position));
            const ::FLOAT top = gui::to_pixels< ::FLOAT>(gui::position<Position>::top(position));
            const ::FLOAT width = gui::to_pixels< ::FLOAT>(gui::dimension<Dimension>::width(dimension));
            const ::FLOAT height = gui::to_pixels< ::FLOAT>(gui::dimension<Dimension>::height(dimension));
            return D2D1::RectF(left, top, left + width, top + height);
        }

        static ::D2D1_COLOR_F colorref_to_color_f(const ::COLORREF colorref)
        {
            return rgba_to_color_f(GetRValue(colorref), GetGValue(colorref), GetBValue(colorref), 255);
        }

        static ::D2D1_COLOR_F rgba_to_color_f(
            const unsigned char red,
            const unsigned char green,
            const unsigned char blue,
            const unsigned char alpha
        )
        {
            return D2D1::ColorF(
                static_cast< ::FLOAT>(red / 255.0),
                static_cast< ::FLOAT>(green / 255.0),
                static_cast< ::FLOAT>(blue / 255.0),
                static_cast< ::FLOAT>(alpha / 255.0)
            );
        }

        static unique_com_ptr< ::ID2D1Brush>::type create_brush(
            canvas_details_type&           canvas,
            const background_details_type& background_details
        )
        {
            const detail::solid_background_details* const p_solid =
                dynamic_cast<const detail::solid_background_details*>(&background_details);
            if (p_solid)
            {
                ::ID2D1SolidColorBrush* rp_brush = NULL;
                const ::HRESULT hr =
                    canvas.CreateSolidColorBrush(
                        rgba_to_color_f(p_solid->red(), p_solid->green(), p_solid->blue(), p_solid->alpha()),
                        D2D1::BrushProperties(),
                        &rp_brush
                    );
                if (FAILED(hr))
                {
                    BOOST_THROW_EXCEPTION(
                        std::system_error(std::error_code(hr, direct2d_category()), "Can't create solid color brush.")
                    );
                }
                return unique_com_ptr< ::ID2D1Brush>::type(rp_brush);
            }

            BOOST_THROW_EXCEPTION(std::invalid_argument("Invalid background details type."));
        }

        static unique_com_ptr< ::ID2D1StrokeStyle>::type create_stroke_style(const int style)
        {
            ::ID2D1StrokeStyle* rp_stroke_style = NULL;
            const ::HRESULT hr =
                direct2d_factory().CreateStrokeStyle(
                    D2D1::StrokeStyleProperties(
                        ::D2D1_CAP_STYLE_ROUND,
                        ::D2D1_CAP_STYLE_ROUND,
                        ::D2D1_CAP_STYLE_ROUND,
                        ::D2D1_LINE_JOIN_ROUND,
                        1.0f,
                        to_stroke_dash_style(style)
                    ),
                    NULL,
                    0,
                    &rp_stroke_style
                );
            if (FAILED(hr))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(hr, direct2d_category()), "Can't create stroke style.")
                );
            }
            return unique_com_ptr< ::ID2D1StrokeStyle>::type(rp_stroke_style);
        }

        static ::D2D1_DASH_STYLE to_stroke_dash_style(const int style)
        {
            switch (style)
            {
            case 0:
                return ::D2D1_DASH_STYLE_SOLID;
            case 1:
                return ::D2D1_DASH_STYLE_DASH;
            case 2:
                return ::D2D1_DASH_STYLE_DOT;
            case 3:
                return ::D2D1_DASH_STYLE_DASH_DOT;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::invalid_argument("Unknown stroke dash style."));
            }
        }

        template <typename String, typename Font, typename Encoder>
        static unique_com_ptr< ::IDWriteTextLayout>::type create_text_layout(
            const String&       text,
            const Font&         font,
            const Encoder&      encoder
        )
        {
            ::IDWriteTextFormat* rp_format = NULL;
            const ::HRESULT create_format_hr =
                direct_write_factory().CreateTextFormat(
                    encoder.encode(font.family()).c_str(),
                    NULL,
                    font.bold() ? ::DWRITE_FONT_WEIGHT_BOLD : ::DWRITE_FONT_WEIGHT_NORMAL,
                    font.italic() ? ::DWRITE_FONT_STYLE_ITALIC : ::DWRITE_FONT_STYLE_NORMAL,
                    ::DWRITE_FONT_STRETCH_NORMAL,
                    static_cast< ::FLOAT>(font.size()),
                    L"",
                    &rp_format
                );
            if (FAILED(create_format_hr))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(create_format_hr, win32_category()), "Can't create text format.")
                );
            }
            const typename unique_com_ptr< ::IDWriteTextFormat>::type p_format(rp_format);

            const std::wstring encoded_text = encoder.encode(text);
            ::RECT rect = {};
            if (::GetClientRect(::GetDesktopWindow(), &rect) == FALSE)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(ERROR_FUNCTION_FAILED, win32_category()),
                        "Can't get client rectangle of the desktop."
                    )
                );
            }
            ::IDWriteTextLayout* rp_layout = NULL;
            const ::HRESULT create_layout_hr =
                direct_write_factory().CreateTextLayout(
                    encoded_text.c_str(),
                    static_cast< ::UINT32>(encoded_text.length()),
                    p_format.get(),
                    static_cast< ::FLOAT>(rect.right - rect.left),
                    static_cast< ::FLOAT>(rect.bottom - rect.top),
                    &rp_layout
                );
            if (FAILED(create_layout_hr))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(create_layout_hr, win32_category()), "Can't create text layout.")
                );
            }
            typename unique_com_ptr< ::IDWriteTextLayout>::type p_layout(rp_layout);

            const ::DWRITE_TEXT_RANGE range = { 0, static_cast< ::UINT32>(encoded_text.length()) };
            p_layout->SetUnderline(font.underline() ? TRUE : FALSE, range);
            p_layout->SetStrikethrough(font.strikeout() ? TRUE : FALSE, range);

            return std::move(p_layout);
        }

        static ::FLOAT radian_to_degree(const double radian)
        {
            static const double pi = 3.14159265358979323846264338327950288;
            return static_cast< ::FLOAT>(radian * 180.0 / pi);
        }


        // forbidden operations

        drawing();


   };


}}}}


#endif