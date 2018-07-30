using Microsoft.EntityFrameworkCore;
using Newtonsoft.Json;
using System.ComponentModel.DataAnnotations.Schema;

namespace MedCad.Models
{
    public class ModelContext : DbContext
    {
        public DbSet<Model> Models { get; set; }

        public DbSet<MetaData> MetaDatas { get; set; }
        public DbSet<Geometry> Geometries { get; set; }
        public DbSet<User> Users { get; set; }
        /*protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<Model>()
                .HasOne(g => g.Geometry)
                .WithOne(m => m.Model)
                .HasForeignKey<Geometry>(gk => gk.ModelId);

            modelBuilder.Entity<Model>()
                .HasOne(m => m.MetaData)
                .WithOne(m => m.Model)
                .HasForeignKey<MetaData>(mk => mk.ModelId);

            modelBuilder.Entity<Model>()
                .HasOne(u => u.User)
                .WithOne(m => m.Model)
                .HasForeignKey<User>(uk => uk.ModelId);
        }*/

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
            => optionsBuilder
                .UseNpgsql("User ID=postgres;Password=20101995;Host=localhost;Port=5432;Database=medbox;Pooling=true;");
    }

    public class Model
    {
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        [JsonIgnore]
        public int ModelId { get; set; }

        public User User { get; set; }

        public MetaData MetaData { get; set; }

        public Geometry Geometry { get; set; } 
    }
}