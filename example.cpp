// inspired by Brandt Westing's blogpost: http://kazenotaiyo.blogspot.com/2010/02/dynamic-plotting-w-vtk.html
// and by the official VTK LinePlot example: https://vtk.org/Wiki/VTK/Examples/Cxx/Plotting/LinePlot

#include "plotter.hpp"

class ExampleVTKRealtimePlotter : public VTKRealtimePlotter<vtkFloatArray, float>
{
    void pre_render() override
    {
        vtkAxis* x_axis = chart_->GetAxis(1);
        vtkAxis* y_axis = chart_->GetAxis(0);
        x_axis->SetRange(0, 7.5);
        y_axis->SetRange(-1, 1);
    }

public:
    ExampleVTKRealtimePlotter(unsigned long timer_interval = 1): VTKRealtimePlotter(timer_interval)
    {
        add_columns({"X", "Sine", "Cosine"});
        
        view_->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
        
        vtkPlot *line = add_plot(vtkChart::LINE, 0, 1);
        line->SetColor(0, 255, 0, 255);
        line->SetWidth(2.5);
        
        line = add_plot(vtkChart::LINE, 0, 2);
        line->SetColor(255, 0, 0, 255);
        line->SetWidth(5.0);

        line->GetPen()->SetLineType(vtkPen::DASH_LINE);

        view_->GetRenderWindow()->SetMultiSamples(4);
        view_->GetRenderWindow()->SetFullScreen(true);
        vtkAxis* x_axis = chart_->GetAxis(1);
        vtkAxis* y_axis = chart_->GetAxis(0);
        x_axis->SetTitle("angle");
        y_axis->SetTitle("sin / cos");
    }
};

int main(int, char *[])
{
    ExampleVTKRealtimePlotter plotter;
    plotter.start();

    constexpr size_t target_num_points = 5000;
    const float increment = 7.5 / (target_num_points - 1);

    for (size_t i = 0; i <= target_num_points; ++i)
    {
        std::this_thread::sleep_for(0.001s);
        const float x = i * increment;
        plotter.insert_values({x, sin(x), cos(x)});
    }

    return 0;
}